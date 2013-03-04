#include <iostream>
#include <utility>
#include <QBrush>
#include <QColor>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Exceptions.h"
#include "PH.h"
#include "Sort.h"
#include "Process.h"
#include "PHScene.h"


PHScene::PHScene(PH* _ph) : ph(_ph) {
    // set background color
    setBackgroundBrush(QBrush(QColor(210, 210, 210)));
}


// render the scene from the related PH graph
#include <QDebug>
void PHScene::doRender(void) {
	
    ////////////////////////////////////////////////ZONE PROBLEME//////////////////////////////////////////////////

    // retrieve graph
	GVGraphPtr graph = ph->toGVGraph();
	
    // create GProcesses linking actual processes (PH info) with GVNodes (display info)
    QList<GVNode> gnodes = graph->nodes();
	for (GVNode &gn : gnodes) {
        for (SortPtr &s : ph->getSorts()) {
            for (ProcessPtr &p : s->getProcesses()) {
                if (gn.name == makeProcessName(p)) {
                    GProcessPtr gp = make_shared<GProcess>(p, gn, graph->getDPI());
                    processes.push_back(gp);
                    p.get()->setGProcess(gp);
                }
               // else{

                 //   throw process_not_found();
                //}
			}
        }
	}
	
    // create GSorts linking actual sorts (PH info) with GVClusters (display info)
	QList<GVCluster> gclusters = graph->clusters();	
	for (GVCluster &gc : gclusters)
		for (SortPtr &s : ph->getSorts())
			if (gc.name == makeClusterName(s->getName()))
                sorts.insert(GSortEntry(s->getName(), make_shared<GSort>(s, gc)));

    ////////////////////////////////////////////////ZONE PROBLEME//////////////////////////////////////////////////

    // create GActions linking actual actions to GVEdges (display info)
    createActions(graph);

    draw();
}


// draw all the elements of the scene
void PHScene::draw(void) {

    clear();
    for (auto &s : sorts)
        addItem(s.second.get());
    for (GActionPtr &a : actions)
		addItem(a->getDisplayItem());

}


// retrieve GSort by its related Sort's name
GSortPtr PHScene::getGSort (const string& s) {
    map<string, GSortPtr>::iterator f = sorts.find(s);
    if (f == sorts.end())
        throw sort_not_found() << sort_info(s);
	return sorts[s];
}

// get all the GSort
map<string, GSortPtr> PHScene::getGSorts(){
    return this->sorts;
}

std::vector<GProcessPtr> PHScene::getProcesses(){
    return processes;
}

std::vector<GActionPtr> PHScene::getActions(){
    return actions;
}


void PHScene::hideActions() {
    for (GActionPtr &action : actions) {
        action->getDisplayItem()->hide();
    }
}


void PHScene::showActions() {

    for (GActionPtr &action : actions) {
        // hide actions related to hidden sorts
        if (!action->getSourceSort()->GSort::isVisible() ||
            !action->getTargetSort()->GSort::isVisible() ||
            !action->getResultSort()->GSort::isVisible()) // optional condition as bounces concern couples of processes in same sorts
        {
                action->getDisplayItem()->hide();
        }
        // show other actions
        else    action->getDisplayItem()->show();
    }
}


void PHScene::updateGraph() {

    GVGraphPtr graph = ph->updateGVGraph(this);

    // update GProcess items' positions
    // using nested loops to make sure that each GVNode matches related GProcess
    list<ProcessPtr> phProcesses = ph->getProcesses();
    for (GVNode &gvnode : graph->nodes())
        for (list<ProcessPtr>::iterator it = phProcesses.begin(); it != phProcesses.end(); ++it)
            if (gvnode.name == makeProcessName(*it)) {
                (*it)->getGProcess()->setNode(gvnode);
                break;
            }

    // update GSort items' positions (including related GProcess items)
    map<string, GSortPtr>::iterator it;
    for(it = sorts.begin(); it != sorts.end(); it++) {
        it->second->updatePosition();
    }

    // create GActions linking actual actions to GVEdges (display info)
    actions.clear();
    createActions(graph);

    for (GActionPtr &a : actions)
        addItem(a->getDisplayItem());

    // hide actions that are related to hidden sorts
    showActions();

}

void PHScene::updateGraphForImport() {

    GVGraphPtr graph = ph->updateGVGraph(this);

    // update GProcess items' positions
    // using nested loops to make sure that each GVNode matches related GProcess
    list<ProcessPtr> phProcesses = ph->getProcesses();
    for (GVNode &gvnode : graph->nodes())
        for (list<ProcessPtr>::iterator it = phProcesses.begin(); it != phProcesses.end(); ++it)
            if (gvnode.name == makeProcessName(*it)) {
                (*it)->getGProcess()->setNode(gvnode);
                break;
            }


    // create GActions linking actual actions to GVEdges (display info)
    actions.clear();
    createActions(graph);


    for (GActionPtr &a : actions)
        addItem(a->getDisplayItem());

    // hide actions that are related to hidden sorts
    showActions();

}


void PHScene::createActions(GVGraphPtr graph) {

    // retrieve list of GVEdge structs from graphviz geometry data
    QList<GVEdge> gEdges = graph->edges();

    // create GAction items
    using std::pair;
    pair<GVEdge*, GVEdge*> edges;
    for (ActionPtr &a : ph->getActions()) {
        edges.first = NULL;
        edges.second = NULL;

        // find graph edges that match the Action
        for (GVEdge &gEdge : gEdges) {

            // check the hit of the Action
            if 	(	makeProcessName(a->getSource()) == gEdge.source
                &&	makeProcessName(a->getTarget()) == gEdge.target
                ) 	edges.first = &gEdge;

            // check the bounce (result) of the Action
            if 	(	makeProcessName(a->getTarget()) == gEdge.source
                &&	makeProcessName(a->getResult()) == gEdge.target
                ) 	edges.second = &gEdge;

            // if match, add Action to objects to be drawn
            if (edges.first != NULL && edges.second != NULL) {
                actions.push_back(make_shared<GAction>(a, *(edges.first), *(edges.second), this));
                break;
            }
        }
    }

}

