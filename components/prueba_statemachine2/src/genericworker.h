/*
 *    Copyright (C)2019 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GENERICWORKER_H
#define GENERICWORKER_H

#include "config.h"
#include <stdint.h>
#include <qlog/qlog.h>

#if Qt5_FOUND
	#include <QtWidgets>
#else
	#include <QtGui>
#endif
#include <ui_mainUI.h>
#include <QStateMachine>
#include <QState>
#include <CommonBehavior.h>


#define CHECK_PERIOD 5000
#define BASIC_PERIOD 100

using namespace std;

typedef map <string,::IceProxy::Ice::Object*> MapPrx;


class GenericWorker :
#ifdef USE_QTGUI
	public QWidget, public Ui_guiDlg
#else
	public QObject
 #endif
{
Q_OBJECT
public:
	GenericWorker(MapPrx& mprx);
	virtual ~GenericWorker();
	virtual void killYourSelf();
	virtual void setPeriod(int p);

	virtual bool setParams(RoboCompCommonBehavior::ParameterList params) = 0;
	QMutex *mutex;




protected:
//State Machine
	QStateMachine Machine_testcpp;

	QState *initialize = new QState();
	QState *compute = new QState();
	QState *start_waiting = new QState();
	QFinalState *finalize = new QFinalState();

//-------------------------

	QTimer timer;
	int Period;

private:


public slots:
//Slots funtion State Machine
	virtual void fun_initialize() = 0;
	virtual void fun_compute() = 0;
	virtual void fun_start_waiting() = 0;
	virtual void fun_finalize() = 0;

//-------------------------
	
signals:
	void kill();
//Signals for State Machine
	void start_waitingtoinitialize();
	void initializetocompute();
	void computetocompute();
	void computetofinalize();

//-------------------------
};

#endif
