#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <iostream>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QImage>
#include <QPainter>
#include <Qt>
#include <QXmlStreamWriter>
#include "axe.h"
#include "Exceptions.h"
#include "Action.h"
#include "IO.h"
#include "PH.h"
#include "PHIO.h"
#include "Sort.h"
#include "Area.h"


using boost::make_shared;
using std::string;
using std::vector;


// process actual parsing, finally
typedef const char* CCHAR;
PHPtr PHIO::parse (string const& input) {

    using namespace axe;
    PHPtr res = make_shared<PH>();

    // debug tool
    /*auto coutRule = [](CCHAR i1, CCHAR i2) {
        std::cout << std::string(i1, i2) << std::endl;
    };*/

    // error
    auto error = r_fail([](CCHAR i1, CCHAR i2) {});

    // comment
    r_rule<const char*> comment;
    // does not work with malformed comments like (*aaa(*bb*):
    comment = r_lit("(*") & *(r_any() - r_lit("*)") - r_lit("(*") | comment) & r_lit("*)");

    // white space
    auto space = *(r_any(" \t") | comment);
    auto endl = r_lit("\n");
    auto trailing_spaces = space & endl;

    // infinity
    auto infinity = r_lit("Inf");

    // process declaration
    string sortName;
    int processes;
    auto sort_name = (r_alpha() | r_char('_')) & *(r_any("_'") | r_alnum());
    auto sort_declaration = (r_str("process") & space & (sort_name >> sortName) & space & r_ufixed(processes)) >> e_ref([&](CCHAR i1, CCHAR i2) {
        SortPtr s = Sort::make(sortName, processes);
        res->addSort(s);
    });
    auto sort_declaration_line = sort_declaration & trailing_spaces;

    // action declaration
    string actSort1, actSort2;
    uint actProc1, actProc2, actProc3;
    double actRate;
    int	actStoch;
    bool infiniteActRate = false;
    auto action_required = (sort_name >> actSort1) & space & r_ufixed(actProc1) & space & r_lit("->") & space & (sort_name >> actSort2) & space & r_ufixed(actProc2) & space & r_ufixed(actProc3);
    auto action_rate = 	(	(infinity >> [&](CCHAR i1, CCHAR i2) { infiniteActRate = true; })
                        | 	(r_double(actRate) >> [&](CCHAR i1, CCHAR i2) { infiniteActRate = false; })
                        );
    auto action_with_rate 	= action_required & space & r_lit("@") & space & action_rate;
    auto action_with_stoch 	= (action_with_rate & space & r_lit("~") & space & r_ufixed(actStoch));
    auto action = 			action_with_stoch >> e_ref([&](CCHAR i1, CCHAR i2) {
                                ActionPtr action = make_shared<Action>(	res->getSort(actSort1)->getProcess(actProc1)
                                                                    ,	res->getSort(actSort2)->getProcess(actProc2)
                                                                    ,	res->getSort(actSort2)->getProcess(actProc3)
                                                                    ,	infiniteActRate, actRate, actStoch);
                                res->addAction(action);
                        })
                        |	action_with_rate >> e_ref([&](CCHAR i1, CCHAR i2) {
                                ActionPtr action = make_shared<Action>(	res->getSort(actSort1)->getProcess(actProc1)
                                                                    ,	res->getSort(actSort2)->getProcess(actProc2)
                                                                    ,	res->getSort(actSort2)->getProcess(actProc3)
                                                                    ,	infiniteActRate, actRate
                                                                    ,	res->getStochasticityAbsorption());
                                res->addAction(action);
                        })
                        |	action_required >> e_ref([&](CCHAR i1, CCHAR i2) {
                                ActionPtr action = make_shared<Action>(	res->getSort(actSort1)->getProcess(actProc1)
                                                                    ,	res->getSort(actSort2)->getProcess(actProc2)
                                                                    ,	res->getSort(actSort2)->getProcess(actProc3)
                                                                    ,	res->getInfiniteDefaultRate(), res->getDefaultRate()
                                                                    ,	res->getStochasticityAbsorption());
                                res->addAction(action);
                        });
    auto action_line = action & trailing_spaces;

    // body
    auto body_line = sort_declaration_line | action_line | trailing_spaces ;

    // footer
    vector<string> initSorts;
    vector<int> initProc;
    auto initial_state = 	(
                            r_lit("initial_state") & space
                            & r_many((sort_name >> e_push_back(initSorts)) & space & (r_ufixed() >> e_push_back(initProc)), space & r_lit(",") & space)
                            & trailing_spaces
                        ) >> e_ref([&](CCHAR i1, CCHAR i2) {
                            for (unsigned int i=0; i < initSorts.size(); i++)
                                res->getSort(initSorts[i])->setActiveProcess(initProc[i]);
                            initSorts.clear();
                            initProc.clear();
                        });
    auto footer_line = initial_state | trailing_spaces;

    // complete file
    auto body = *body_line;
    auto footer = *footer_line;
    auto ph = (body & footer & r_end()) | error;
    auto result = ph(input.c_str(), input.c_str() + input.length());

    if (!result.matched)
        throw ph_parse_error();

    return res;
}


// parse file
PHPtr PHIO::parseFile (string const& path) {

    // dump content using phc -l dump
    // (this command transforms complex PH instructions in basic ones)
    QString phc = "phc";
    QStringList args;
    args << "-l" << "dump" << "-i" << QString::fromUtf8(path.c_str()) << "--no-debug";
    QProcess *phcProcess = new QProcess();
    phcProcess->start(phc, args);
    if (!phcProcess->waitForStarted())
        throw pint_program_not_found() << file_info("phc");

    // read result
    QByteArray stderr;
    QByteArray stdout;
    while (!phcProcess->waitForFinished()) {
        stderr += phcProcess->readAllStandardError();
        stdout += phcProcess->readAllStandardOutput();
    }
    stderr += phcProcess->readAllStandardError();
    stdout += phcProcess->readAllStandardOutput();
    delete phcProcess;

    // parse dump
    if (!stderr.isEmpty())
        throw pint_phc_crash() << parse_info(QString(stderr).toStdString());

    return parse(QString(stdout).toStdString());
}


// can parse the PH file which path is given as parameter?
bool PHIO::canParseFile (string const& path) {
    try {
        parseFile(path);
    } catch (exception_base& x) {
        return false;
    }
    return true;
}


// write PH file
void PHIO::writeToFile (string const& path, PHPtr ph) {
    IO::writeFile(path, ph->toString());
}


// save PH as PNG image
void PHIO::exportToPNG(PHPtr ph, QString name) {

    // create the image and render it
    // TODO make margins (currently: 4 pixels) configuration variables
    QImage* image = new QImage(ph->getGraphicsScene()->width()+4, ph->getGraphicsScene()->height()+4, QImage::Format_ARGB32_Premultiplied);
    QPainter* p = new QPainter();
    p->begin(image);
    p->setRenderHint(QPainter::Antialiasing);
    ph->getGraphicsScene()->render(p);
    p->end();

    // add .png to the name if necessary
    if (name.indexOf(QString(".png"), 0, Qt::CaseInsensitive) < 0)
        name += ".png";

    // save it
    image->save(name, "PNG");
}


// export preferences to XML
void PHIO::exportXMLMetadata(MainWindow *window, QFile &output){

    QXmlStreamWriter stream(&output);

    Area* area = (Area*)window->getCentraleArea()->currentSubWindow()->widget();
    MyArea* myarea = ((Area*)window->getCentraleArea()->currentSubWindow()->widget())->myArea;
    QList<QTreeWidgetItem*> sortsFound = area->treeArea->groupsTree->findItems("", Qt::MatchContains, 0);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();

    stream.writeStartElement("graph_metadata");
    stream.writeStartElement("global");

    stream.writeStartElement("ph_file");
    stream.writeTextElement("name", window->getCentraleArea()->currentSubWindow()->windowTitle());
    stream.writeTextElement("path", area->path);
    stream.writeEndElement(); // ph_file

    stream.writeStartElement("styles");
    stream.writeTextElement("bg_color", myarea->getPHPtr()->getGraphicsScene()->backgroundBrush().color().name());
    stream.writeTextElement("sort_color", "#073642");
    stream.writeTextElement("process_color", "#EEE8D5");
    stream.writeTextElement("text_bg_color", "#0A0A0A");
    stream.writeTextElement("sort_font", "");
    stream.writeTextElement("process_font", "");
    stream.writeTextElement("text_font", "TypeWriter");
    stream.writeEndElement(); // styles

    stream.writeStartElement("scene");
    stream.writeTextElement("height", QString::number(window->height()));
    stream.writeTextElement("width", QString::number(window->width()));
    stream.writeEndElement(); //scene

    stream.writeEndElement(); // global

    stream.writeStartElement("sorts");
    for (SortPtr &a: myarea->getPHPtr()->getSorts()){
        stream.writeStartElement("sort");
        stream.writeAttribute("name", QString::fromStdString(a->getName()));
        stream.writeAttribute("visible", QString::number(myarea->getPHPtr()->getGraphicsScene()->getGSort(a->getName())->GSort::isVisible()));

        stream.writeStartElement("pos");
        stream.writeAttribute("x", "");
        stream.writeAttribute("y", "");
        stream.writeEndElement(); // pos

        stream.writeStartElement("size");
        stream.writeAttribute("w", "");
        stream.writeAttribute("h", "");
        stream.writeEndElement(); // size

        stream.writeTextElement("color", myarea->getPHPtr()->getGraphicsScene()->getGSort(a->getName())->getRect()->brush().color().name());

        stream.writeStartElement("label");
        stream.writeAttribute("text", myarea->getPHPtr()->getGraphicsScene()->getGSort(a->getName())->getText()->toPlainText());

        stream.writeTextElement("font", myarea->getPHPtr()->getGraphicsScene()->getGSort(a->getName())->getText()->font().toString());

        stream.writeStartElement("pos");
        stream.writeAttribute("x", "");
        stream.writeAttribute("y", "");
        stream.writeEndElement(); //pos

        stream.writeEndElement(); // label

        stream.writeStartElement("processes");
        stream.writeAttribute("nb", QString::number(a->getProcesses().size()));

        for (ProcessPtr &b : a->getProcesses()){
            stream.writeStartElement("process");
            stream.writeAttribute("i", QString::number(b->getNumber()));

            stream.writeStartElement("pos");
            stream.writeAttribute("x", "");
            stream.writeAttribute("y", "");
            stream.writeEndElement(); // pos

            stream.writeStartElement("size");
            stream.writeAttribute("w", "");
            stream.writeAttribute("h", "");
            stream.writeEndElement(); // size

            stream.writeEndElement(); // process
        }

        stream.writeEndElement(); // processes

        stream.writeEndElement(); // sort
    }

    stream.writeEndElement(); // sorts

    stream.writeStartElement("sort_groups");

    for (QTreeWidgetItem* &a : sortsFound){
            if (a->parent() == NULL){
            stream.writeStartElement("group");
            stream.writeAttribute("name", a->text(0));
            stream.writeAttribute("visible", QString::number(!a->font(0).italic()));
            stream.writeTextElement("color", a->foreground(0).color().name());
            // sorts list
            if (a->childCount()) {
                stream.writeStartElement("sorts");
                for (int i(0); i < a->childCount(); i++) {
                    stream.writeStartElement("sort");
                    stream.writeAttribute("name", a->child(i)->text(0));
                    stream.writeEndElement(); // sorts
                }
                stream.writeEndElement();
            }
            stream.writeEndElement(); // group

        }
    }


    stream.writeEndElement(); // sort_groups

    stream.writeEndElement(); // graph_metadata

    stream.writeEndDocument();
}
