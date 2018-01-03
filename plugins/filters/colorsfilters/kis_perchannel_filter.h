/*
 * This file is part of Krita
 *
 * Copyright (c) 2004 Cyrille Berger <cberger@cberger.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#ifndef _KIS_PERCHANNEL_FILTER_H_
#define _KIS_PERCHANNEL_FILTER_H_

#include <QPair>
#include <QList>

#include <filter/kis_color_transformation_filter.h>
#include <filter/kis_color_transformation_configuration.h>
#include <kis_config_widget.h>
#include <kis_paint_device.h>
#include "ui_wdg_perchannel.h"

#include "virtual_channel_info.h"


class WdgPerChannel : public QWidget, public Ui::WdgPerChannel
{
    Q_OBJECT

public:
    WdgPerChannel(QWidget *parent) : QWidget(parent) {
        setupUi(this);
    }
};

class KisPerChannelFilterConfiguration
        : public KisColorTransformationConfiguration
{
public:
    KisPerChannelFilterConfiguration(int n);
    ~KisPerChannelFilterConfiguration() override;

    using KisFilterConfiguration::fromXML;
    using KisFilterConfiguration::toXML;
    using KisFilterConfiguration::fromLegacyXML;

    void fromLegacyXML(const QDomElement& root) override;

    void fromXML(const QDomElement& e) override;
    void toXML(QDomDocument& doc, QDomElement& root) const override;

    void setCurves(QList<KisCubicCurve> &curves) override;
    static inline void initDefaultCurves(QList<KisCubicCurve> &curves, int nCh);
    bool isCompatible(const KisPaintDeviceSP) const override;

    const QVector<QVector<quint16> >& transfers() const;
    const QList<KisCubicCurve>& curves() const override;
private:
    QList<KisCubicCurve> m_curves;

private:
    void updateTransfers();
private:
    QVector<QVector<quint16> > m_transfers;
};


/**
 * This class is generic for filters that affect channel separately
 */
class KisPerChannelFilter
        : public KisColorTransformationFilter
{
public:
    KisPerChannelFilter();
public:
    KisConfigWidget * createConfigurationWidget(QWidget* parent, const KisPaintDeviceSP dev) const override;
    KisFilterConfigurationSP  factoryConfiguration() const override;

    KoColorTransformation* createTransformation(const KoColorSpace* cs, const KisFilterConfigurationSP config) const override;

    bool needsTransparentPixels(const KisFilterConfigurationSP config, const KoColorSpace *cs) const override;

    static inline KoID id() {
        return KoID("perchannel", i18n("Color Adjustment"));
    }
private:
};

class KisPerChannelConfigWidget : public KisConfigWidget
{
    Q_OBJECT

public:
    KisPerChannelConfigWidget(QWidget * parent, KisPaintDeviceSP dev, Qt::WindowFlags f = 0);
    ~KisPerChannelConfigWidget() override;

    void setConfiguration(const KisPropertiesConfigurationSP config) override;
    KisPropertiesConfigurationSP  configuration() const override;

private Q_SLOTS:
    virtual void setActiveChannel(int ch);
    void logHistView();
    void resetCurve();


private:

    QVector<VirtualChannelInfo> m_virtualChannels;
    int m_activeVChannel;


    // private routines
    inline QPixmap getHistogram();
    inline QPixmap createGradient(Qt::Orientation orient /*, int invert (not used now) */);

    // members
    WdgPerChannel * m_page;
    KisPaintDeviceSP m_dev;
    KisHistogram *m_histogram;
    mutable QList<KisCubicCurve> m_curves;

    // scales for displaying color numbers
    double m_scale;
    double m_shift;
    bool checkReset;
};

#endif
