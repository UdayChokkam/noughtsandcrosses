#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

#include <iostream>

#include <QDebug>
#include <QString>

#include "nxdata.h"

NXData::NXData()
{

    makeGrid();
}

NXData::~NXData()
{
}

void NXData::setGridDim(std::size_t dim)
{
    gridDim = dim;
    makeGrid();
}

void NXData::makeGrid()
{

    data.resize(gridDim);
    for (std::size_t i {0}; i<data.size(); i++) {
        for (std::size_t n{0}; n<gridDim; n++) {
            data[i].push_back(QString());
        }
    }
}

bool NXData::validIndex(std::size_t row, std::size_t column)
{
    if (row < gridDim && column < gridDim)
        return true;
    else
        return false;

}

QString NXData::setItem(std::size_t row, std::size_t column, QString item)
{
    if (validIndex(row, column)) {
        data[row][column] = item;
        QString status = checkWin();
        return status;
    }
    else
        throw std::invalid_argument("'row' or 'column' exceeds grid dimensions");
}

QString NXData::getItem(std::size_t row, std::size_t column)
{
    if (validIndex(row, column))
        return data[row][column];
    else
        throw std::invalid_argument("'row' or 'column' exceeds grid dimensions");
}

QString NXData::checkWin()
{

    std::vector<QString> checks;
    checks.push_back(checkRows());
    checks.push_back(checkColumns());
    checks.push_back(checkDiags());


    if (std::all_of(checks.begin(), checks.end(), [](QString s){ return s=="draw"; }))
        return "draw";

    else {
        for (QString s : checks) {
            if (!s.isEmpty() && s!="draw") {
                return s;
            }
        }
    }

    return "";
}

bool NXData::vectorEqual(std::vector<QString> vec)
{

    for (std::size_t i {1}; i<vec.size(); i++) {
        if (vec[i]!=vec[i-1])
            return false;
    }

    return true;
}

bool NXData::vectorDraw(std::vector<QString> vec)
{

    bool containsNought = false;
    bool containsCross = false;

    for (std::size_t i {0}; i<vec.size(); i++) {
        if (vec[i]=="nought")
            containsNought = true;
        else if (vec[i]=="cross")
            containsCross = true;
    }

    if (containsNought && containsCross) {
        return true;
    }
    else {
        return false;
    }
}

QString NXData::checkRows()
{

    return checkDim(data);
}

QString NXData::checkColumns()
{

    std::vector<std::vector<QString>> columns;


    for (std::size_t c {0}; c<gridDim; c++) {


        std::vector<QString> col;


        for (std::size_t r {0}; r<gridDim; r++)
            col.push_back(data[r][c]);
        columns.push_back(col);
    }

    return checkDim(columns);
}

QString NXData::checkDiags()
{

    std::vector<std::vector<QString>> diags;
    diags.resize(2);


    for (std::size_t i {0}; i<gridDim; i++) {
        diags[0].push_back(data[i][i]);
        diags[1].push_back(data[i][gridDim-i-1]);
    }

    return checkDim(diags);
}

QString NXData::checkDim(std::vector<std::vector<QString>> dims)
{

    std::vector<bool> draws;
    draws.resize(dims.size());

    std::fill(draws.begin(), draws.end(), false);


    for (std::size_t i {0}; i<dims.size(); i++) {

        draws[i] = vectorDraw(dims[i]);

        if (vectorEqual(dims[i]) && !dims[i][0].isEmpty()) {

            return dims[i][0];
        }
    }


    if (std::all_of(draws.begin(), draws.end(), [](bool b){ return b; })) {
        return "draw";
    }

    return "";
}

QString NXData::getIconPath(QString item)
{
    QString iconPath = "../images/" + item + ".png";
    return iconPath;
}
