#ifndef NXDATA_H
#define NXDATA_H

#include <vector>
#include <memory>

#include <QString>

class NXData
{

public:
    NXData();

    ~NXData();


    QString setItem(std::size_t row, std::size_t column, QString item);


    QString getItem(std::size_t row, std::size_t column);

    QString getIconPath(QString item);

protected:

    std::vector<std::vector<QString>> data;

    QString checkWin();

private:

    std::size_t gridDim = 3;

    void setGridDim(std::size_t dim);

    void makeGrid();

    QString checkRows();

    QString checkColumns();

    QString checkDiags();

    QString checkDim(std::vector<std::vector<QString>> dims);

    bool vectorEqual(std::vector<QString> vec);

    bool vectorDraw(std::vector<QString> vec);

    bool validIndex(std::size_t row, std::size_t column);
};

#endif
