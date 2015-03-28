/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
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

#ifndef QQUICKABSTRACTSTACKVIEW_P_H
#define QQUICKABSTRACTSTACKVIEW_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtQuickControls/private/qquickabstractcontainer_p.h>

QT_BEGIN_NAMESPACE

class QQmlV4Function;
class QQuickTransition;
class QQuickStackElement;
class QQuickStackAttached;
class QQuickAbstractStackViewPrivate;

class Q_QUICKCONTROLS_EXPORT QQuickAbstractStackView : public QQuickAbstractContainer
{
    Q_OBJECT
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged FINAL)
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged FINAL)
    Q_PROPERTY(QQuickItem *currentItem READ currentItem NOTIFY currentItemChanged FINAL)
    Q_PROPERTY(QVariant initialItem READ initialItem WRITE setInitialItem FINAL)
    Q_PROPERTY(QQuickTransition *popEnter READ popEnter WRITE setPopEnter NOTIFY popEnterChanged FINAL)
    Q_PROPERTY(QQuickTransition *popExit READ popExit WRITE setPopExit NOTIFY popExitChanged FINAL)
    Q_PROPERTY(QQuickTransition *pushEnter READ pushEnter WRITE setPushEnter NOTIFY pushEnterChanged FINAL)
    Q_PROPERTY(QQuickTransition *pushExit READ pushExit WRITE setPushExit NOTIFY pushExitChanged FINAL)

public:
    explicit QQuickAbstractStackView(QQuickItem *parent = Q_NULLPTR);
    ~QQuickAbstractStackView();

    static QQuickStackAttached *qmlAttachedProperties(QObject *object);

    bool busy() const;
    int depth() const;
    QQuickItem *currentItem() const;

    enum Status {
        Inactive = 0,
        Deactivating = 1,
        Activating = 2,
        Active = 3
    };
    Q_ENUM(Status)

    QVariant initialItem() const;
    void setInitialItem(const QVariant &item);

    QQuickTransition *popEnter() const;
    void setPopEnter(QQuickTransition *enter);

    QQuickTransition *popExit() const;
    void setPopExit(QQuickTransition *exit);

    QQuickTransition *pushEnter() const;
    void setPushEnter(QQuickTransition *enter);

    QQuickTransition *pushExit() const;
    void setPushExit(QQuickTransition *exit);

    enum LoadBehavior {
        DontLoad,
        ForceLoad
    };
    Q_ENUM(LoadBehavior)

    Q_INVOKABLE QQuickItem *get(int index, LoadBehavior behavior = DontLoad);
    Q_INVOKABLE QQuickItem *find(const QJSValue &callback, LoadBehavior behavior = DontLoad);

    enum Operation {
        Transition,
        Immediate
    };
    Q_ENUM(Operation)

    Q_INVOKABLE void push(QQmlV4Function *args);
    Q_INVOKABLE void pop(QQmlV4Function *args);
    Q_INVOKABLE void replace(QQmlV4Function *args);

public Q_SLOTS:
    void clear();

Q_SIGNALS:
    void busyChanged();
    void depthChanged();
    void currentItemChanged();
    void popEnterChanged();
    void popExitChanged();
    void pushEnterChanged();
    void pushExitChanged();

protected:
    void componentComplete() Q_DECL_OVERRIDE;
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QQuickAbstractStackView)
    Q_DECLARE_PRIVATE(QQuickAbstractStackView)
};

class QQuickStackAttachedPrivate;

class Q_QUICKCONTROLS_EXPORT QQuickStackAttached : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int index READ index NOTIFY indexChanged FINAL)
    Q_PROPERTY(QQuickAbstractStackView::Status status READ status NOTIFY statusChanged FINAL)

public:
    explicit QQuickStackAttached(QQuickItem *parent = Q_NULLPTR);

    int index() const;
    QQuickAbstractStackView::Status status() const;

Q_SIGNALS:
    void indexChanged();
    void statusChanged();

private:
    Q_DISABLE_COPY(QQuickStackAttached)
    Q_DECLARE_PRIVATE(QQuickStackAttached)
};

QT_END_NAMESPACE

QML_DECLARE_TYPEINFO(QQuickAbstractStackView, QML_HAS_ATTACHED_PROPERTIES)
QML_DECLARE_TYPE(QQuickAbstractStackView)

#endif // QQUICKABSTRACTSTACKVIEW_P_H
