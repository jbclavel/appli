#ifndef TREEAREA_H
#define TREEAREA_H

#include <QWidget>
#include <QTreeWidget>
#include <QPushButton>
#include <QLineEdit>
#include "PH.h"
#include "MyArea.h"


/**
  * @class TreeArea
  * @brief Tree Wigets extends QWidget
  *
  */
class TreeArea : public QWidget
{
    Q_OBJECT
public:

    /**
      * @brief constructor
      * @brief QWidget parent, the widget containing the TextArea, which is the Area
      *
      */
    TreeArea(QWidget *parent);

    /**
      * @brief pointer to the PH
      *
      */
    PHPtr myPHPtr;

    /**
      * @brief pointer to the myArea
      *
      */
    MyArea* myArea;

    /**
      * @brief pointer to the sorts QTreeWidget
      *
      */
    QTreeWidget* sortsTree;

    /**
      * @brief pointer to the groups QTreeWidget
      *
      */
    QTreeWidget* groupsTree;

    /**
      * @brief pointer to the search button
      *
      */
    QPushButton* searchButton;

    /**
      * @brief pointer to the cancelSearch button
      *
      */
    QPushButton* cancelSearchButton;

    /**
      * @brief pointer to the search line edit
      *
      */
    QLineEdit* searchBox;

    /**
      * @brief pointer to the addToGroup button
      *
      */
    QPushButton* addToGroupButton;

    /**
      * @brief pointer to the removeGroup button
      *
      */
    QPushButton* removeGroupButton;

    /**
      * @brief pointer to the addGroup button
      *
      */
    QPushButton* addGroupButton;

    /**
      * @brief list containing all the sorts. Built when the file is opened
      *
      */
    QList<QTreeWidgetItem*> sorts;

    /**
      * @brief list containing all the groups.
      *
      */
    QList<QTreeWidgetItem*> groups;

    /**
      * @brief map containing the colors of the groups
      *
      */
    QMap<QTreeWidgetItem*, QColor>* groupsPalette;

    /**
      * @brief list containing the standard colors for the groups
      *
      */
    QList<QColor>* palette;

    /**
      * @brief flag that indicates that user clicked an item in sortsTree
      */
    static const int clickInSortsTree;
    /**
      * @brief flag that indicates that user clicked an item in groupsTree
      */
    static const int clickInGroupsTree;



signals:

public slots:

    /**
      * @brief build the base tree. Called on opening
      *
      */
    void build();

    /**
      * @brief search a sort. Slot linked with the search button signal
      *
      */
    void searchSort();

    /**
      * @brief cancel the search of the sort. Shows all the items in the tree
      *
      */
    void cancelSearch();

    /**
      * @brief add a group to the groupsTree
      *
      */
    void addGroup();

    /**
      * @brief remove the selected group from the groupsTree
      *
      */
    void remove();

    /**
      * @brief add a sort to a selected group
      *
      */
    void addToGroup();

    /**
      * @brief menu to show when the sort is clicked
      *
      */
    void sortsItemClicked(const QPoint& pos);

    /**
      * @brief hide a sort
      * @param int a flag that takes the value TreeArea::clickInSortsTree or TreeArea::clickInGroupsTree
      *
      */    
    void hideSort(int clickedTree);

    /**
      * @brief show a sort
      * @param int a flag that takes the value TreeArea::clickInSortsTree or TreeArea::clickInGroupsTree
      *
      */
    void showSort(int clickedTree);

    /**
      * @brief change sort color
      * @param int a flag that takes the value TreeArea::clickInSortsTree or TreeArea::clickInGroupsTree
      *
      */
    void changeSortColor(int clickedTree);

    /**
      * @brief change sort's rect color
      *
      */
    void changeSortRectColor(QTreeWidgetItem*, QColor*);

    /**
      * @brief menu to show when the sort is clicked
      *
      */
    void groupsItemClicked(const QPoint& pos);

    /**
      * @brief hide a sort
      *
      */
    void hideGroup();

    /**
      * @brief show a sort
      *
      */
    void showGroup();

    /**
      * @brief change sort color
      *
      */
    void changeGroupColor();

    /**
      * @brief slot signifying that the item is clicked from the sortsTree and calls hideSort(1)
      *
      */
    void hideSortClickedFromSort();

    /**
      * @brief slot signifying that the item is clicked from the sortsTree and calls showSort(1)
      *
      */
    void showSortClickedFromSort();

    /**
      * @brief slot signifying that the item is clicked from the sortsTree and calls changeSortColor(1)
      *
      */
    void changeSortColorClickedFromSort();

    /**
      * @brief slot signifying that the item is clicked from the groupsTree and calls hideSort(2)
      *
      */
    void hideSortClickedFromGroup();

    /**
      * @brief slot signifying that the item is clicked from the groupsTree and calls showSort(2)
      *
      */
    void showSortClickedFromGroup();

    /**
      * @brief slot signifying that the item is clicked from the groupsTree and calls changeSortColor(2)
      *
      */
    void changeSortColorClickedFromGroup();





};

#endif // TREEAREA_H
