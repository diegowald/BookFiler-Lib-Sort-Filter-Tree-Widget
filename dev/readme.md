I need a QT5 widget written in C++. The Libraries used are QT, Boost, and sqlite3. I need a custom `QTreeView` written that is able to be sorted, filtered, and edited using sqlite3 as the backend. To Sort and filter you need to use SQL queries to reorder the data. You may use `QSortFilterProxyModel` to help with sorting and filtering. The compiler I use is GCC. You may use MinGW on windows or GCC on linux to build. I don't compile with visual studio.

The `QTreeView` columns must be dynamically created to be the same as the `sqlite3` table passed to the widget. You must use an SQL query to detect the columns in the table and dynamically created a view for it. `sqlite3` table must have the columns `guid` and `guid_parent` (the name of the column can be different, the columns must have the same purpose) so that the tree view children can be built off this.

## `QTreeView` column dynamic sizing

Here is an example of how the `QTreeView` will by dynamically created by the `sqlite3` table:

### Example 1

`sqlite3` table columns: guid, parent_guid, Subject, Important, Attachment, From, Date, Size

![Style 1](https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget/blob/main/dev/tree-view-design-1.png?raw=true)

### Example 2

`sqlite3` table columns: guid, parent_guid, Name

![Style 2](https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget/blob/main/dev/tree-view-design-2.png?raw=true)

