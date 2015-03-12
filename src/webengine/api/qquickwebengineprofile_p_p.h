/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQUICKWEBENGINEPROFILE_P_P_H
#define QQUICKWEBENGINEPROFILE_P_P_H

#include "browser_context_adapter_client.h"
#include "qquickwebengineprofile_p.h"

#include <QExplicitlySharedDataPointer>
#include <QMap>
#include <QPointer>

QT_BEGIN_NAMESPACE

class QQuickWebEngineDownloadItem;
class QQuickWebEngineSettings;

class QQuickWebEngineProfilePrivate : public QtWebEngineCore::BrowserContextAdapterClient {
public:
    Q_DECLARE_PUBLIC(QQuickWebEngineProfile)
    QQuickWebEngineProfilePrivate(QtWebEngineCore::BrowserContextAdapter* browserContext, bool ownsContext);
    ~QQuickWebEngineProfilePrivate();

    QtWebEngineCore::BrowserContextAdapter *browserContext() const { return m_browserContext; }
    QQuickWebEngineSettings *settings() const { return m_settings.data(); }

    void cancelDownload(quint32 downloadId);
    void downloadDestroyed(quint32 downloadId);

    void downloadRequested(DownloadItemInfo &info) Q_DECL_OVERRIDE;
    void downloadUpdated(const DownloadItemInfo &info) Q_DECL_OVERRIDE;

private:
    friend class QQuickWebEngineViewPrivate;
    QQuickWebEngineProfile *q_ptr;
    QScopedPointer<QQuickWebEngineSettings> m_settings;
    QtWebEngineCore::BrowserContextAdapter *m_browserContext;
    QExplicitlySharedDataPointer<QtWebEngineCore::BrowserContextAdapter> m_browserContextRef;
    QMap<quint32, QPointer<QQuickWebEngineDownloadItem> > m_ongoingDownloads;
};

QT_END_NAMESPACE

#endif // QQUICKWEBENGINEPROFILE_P_P_H
