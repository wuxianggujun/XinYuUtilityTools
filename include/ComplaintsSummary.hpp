//
// Created by wuxianggujun on 2024/6/21.
//

#ifndef XINYUUTILITYTOOLS_COMPLAINTSSUMMARY_HPP
#define XINYUUTILITYTOOLS_COMPLAINTSSUMMARY_HPP

#include <xlsxdocument.h>
#include <xlsxcellrange.h>
#include <xlsxworkbook.h>
#include <xlsxformat.h>
#include <xlsxchart.h>
#include <xlsxrichstring.h>
#include <xlsxconditionalformatting.h>
#include <xlsxchartsheet.h>

QXLSX_USE_NAMESPACE

class ComplaintsSummary {
private:
    int m_sequence;
    QString m_city;
    QString m_complaintLocation;
    double m_longitude;
    double m_latitude;
    int m_complaintVolume;
    QString m_complaintSource;
    QString m_complaintUserNumber;
    QString m_solutionMethod;
    QString m_area;
    bool m_resolvedStatus;
    QVariant m_remarks;
    bool m_elevatorStop;
};


#endif //XINYUUTILITYTOOLS_COMPLAINTSSUMMARY_HPP
