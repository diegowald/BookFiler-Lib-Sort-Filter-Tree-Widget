/*
 * @name BookFiler Library - Sort Filter Tree Widget
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief sqlite3 based tree widget.
 */

/*
   @brief Provides a simple tree model to show how to create and use
  hierarchical models.

  Examples
  https://code.qt.io/cgit/qt/qtbase.git/tree/examples/widgets/itemviews/stardelegate/main.cpp?h=5.14
*/

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QStringList>

// Local Project
#include "TreeModel.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

TreeModel::TreeModel(QObject *parent) : QAbstractItemModel(parent) {
  rootItem = new TreeItem({tr("Name"), tr("Value")});
}

TreeModel::~TreeModel() { delete rootItem; }

/* Custom methods
 *
 *
 *
 *
 */

void TreeModel::addData(std::shared_ptr<sqlite3> database, std::string tableName,
                          std::string idColumn, std::string parentColumn) {
  // TODO: set data
}

/* Base methods for the view
 *
 *
 *
 */

int TreeModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return static_cast<TreeItem *>(parent.internalPointer())->columnCount();
  return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  TreeItem *item = static_cast<TreeItem *>(index.internalPointer());

  // Normal data display
  if (role == Qt::DisplayRole) {
    return item->data(index.column());
  }
  // Data displayed in the edit box
  else if (role == Qt::EditRole) {
    return item->data(index.column());
  }

  // for all else
  return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return Qt::NoItemFlags;

  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable |
         Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                                 int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return rootItem->data(section);

  return QVariant();
}

QModelIndex TreeModel::index(int row, int column,
                               const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  TreeItem *parentItem;

  if (!parent.isValid())
    parentItem = rootItem;
  else
    parentItem = static_cast<TreeItem *>(parent.internalPointer());

  TreeItem *childItem = parentItem->child(row);
  if (childItem)
    return createIndex(row, column, childItem);
  return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid())
    return QModelIndex();

  TreeItem *childItem = static_cast<TreeItem *>(index.internalPointer());
  TreeItem *parentItem = childItem->parentItem();

  if (parentItem == rootItem)
    return QModelIndex();

  return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const {
  TreeItem *parentItem;
  if (parent.column() > 0)
    return 0;

  if (!parent.isValid())
    parentItem = rootItem;
  else
    parentItem = static_cast<TreeItem *>(parent.internalPointer());

  return parentItem->childCount();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value,
                          int role) {
  if (role) {
    // TODO
  }
  TreeItem *item = static_cast<TreeItem *>(index.internalPointer());
  item->setData(index.column(), value);
  return true;
}

Qt::DropActions TreeModel::supportedDropActions() const {
  return Qt::CopyAction | Qt::MoveAction;
}

bool TreeModel::removeRows(int row, int count, const QModelIndex &parent) {
  TreeItem *parentItem = static_cast<TreeItem *>(parent.internalPointer());
  parentItem->removeChild(row, count);
  return true;
}

} // namespace widget
} // namespace bookfiler
