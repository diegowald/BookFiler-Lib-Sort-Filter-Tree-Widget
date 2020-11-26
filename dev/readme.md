I need a QT5 widget written in C++. The Libraries used are QT, Boost, and sqlite3. I need a custom `QTreeView` written that is able to be sorted, filtered, and edited using sqlite3 as the backend. To Sort and filter you need to use SQL queries to reorder the data. You may use `QSortFilterProxyModel` to help with sorting and filtering. 

I already started on the code. See the header I started for how to use each method of the widget [/src/UI/MainWidget.hpp](https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget/blob/main/src/UI/MainWidget.hpp).

## Compiler and compatability

Program must compile on Windows and Linux. For Windows, use MinGW for compiling. For Linux use GCC. Use cmake as the build scipt.

## `QTreeView` column dynamic sizing

The `QTreeView` columns must be dynamically created to be the same as the `sqlite3` table passed to the widget. You must use an SQL query to detect the columns in the table and dynamically create a view for it. `sqlite3` table must have the columns `guid` and `guid_parent` (the name of the column can be different, the columns must have the same purpose) so that the tree view children can be built off this. Here is an example of how the `QTreeView` will by dynamically created by the `sqlite3` table:

### Example 1

`sqlite3` table columns: guid, parent_guid, Subject, Important, Attachment, From, Date, Size. Hidden columns: guid, parent_guid.

![Style 1](https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget/blob/main/dev/tree-view-design-1.png?raw=true)

### Example 2

`sqlite3` table columns: guid, parent_guid, Name. Hidden columns: guid, parent_guid.

![Style 2](https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget/blob/main/dev/tree-view-design-2.png?raw=true)

## Coding Standards
Always use the standard library when possible. Use `std::shared_ptr` and `std::unique_ptr` instead of raw pointers whenever possible. use `boost` if some method does not exist in standard library. Finally use `QT5` as the last option.

Separate all graphical GUI code into the `/src/UI/` directory. Anything with `QT` should be in the `/src/UI/` directory. All logic and non-GUI code goes into the `/src/core/` directory.

## Deliverables

* Clean and commented code that follows the general design already provided and discussed here
* A working example [/src_example/example00/main.cpp](https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget/blob/main/src_example/example00/main.cpp).

