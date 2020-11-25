/*
 * @name BookFiler Library - Sort Filter Tree Widget
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief sqlite3 based tree widget.
 */

#ifndef BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_ITEM_H
#define BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_ITEM_H

// config
#include "../core/config.hpp"

/* sqlite3 3.33.0
 * License: PublicDomain
 */
#include <sqlite3.h>

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QVariant>
#include <QVector>

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {
/*
 * @brief A container for items of data supplied by the simple tree model.
 */
class TreeItem {
public:
  explicit TreeItem(const QVector<QVariant> &data,
                      TreeItem *parentItem = nullptr);
  ~TreeItem();

  void appendChild(TreeItem *child);
  void removeChild(int row, int count);

  TreeItem *child(int row);
  int childCount() const;
  int columnCount() const;
  QVariant data(int column) const;
  void setData(int column, QVariant value);
  int row() const;
  TreeItem *parentItem();

private:
  QVector<TreeItem *> m_childItems;
  QVector<QVariant> m_itemData;
  TreeItem *m_parentItem;
};

class TreeItemEditor : public QComboBox {
  Q_OBJECT
signals:
  void editingFinished();

public:
  TreeItemEditor(QWidget *parent = nullptr);
  ~TreeItemEditor(){};
};

class TreeItemDelegate : public QStyledItemDelegate {
  Q_OBJECT
public:
  TreeItemDelegate();
  ~TreeItemDelegate() {}

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const;

private:
  void commitAndCloseEditor();
};

} // namespace widget
} // namespace bookfiler

#endif // BOOKFILER_LIBRARY_SORT_FILTER_TREE_WIDGET_ITEM_H
