#include "serverthread.h"

#include <QCoreApplication>
#include <QTextCodec>
#include <QDebug>

ServerThread::ServerThread(QTcpSocket* qsocket, QObject *parent)
    : QThread{parent}
{
    // 指针赋给类中的变量，进行服务
    threadSocket = qsocket;

    // 设定data路径
    DATAHOME.setPath(QCoreApplication::applicationDirPath()+"/data");
}

// 服务逻辑
void ServerThread::run() {
    // 检测是否可以接收数据
    connect( threadSocket, &QTcpSocket::readyRead, this, [=]() {
        array = threadSocket->readAll();    // 读出数据
        qDebug() << "client: "+array;

        // 针对array进行服务反馈
        reply();
    });

    // 关闭连接
    connect( threadSocket, &QTcpSocket::disconnected, this, [=]() {
        threadSocket->close();
        threadSocket->deleteLater();
        qDebug() << "Socket disconnected.";

        // 发射结束信号
        emit exit_return();
    });

    // 进入时间循环
    exec();
}

void ServerThread::reply() {
    QDir tempDir(DATAHOME);

    QString cmd = QString(array);
    QStringList cmdList = cmd.split(" ");   // 分割后的字符串
    QString returnStr = "";   // 要返回的信息

    // 公操作服务***************************************************************************
    // 进行mysql操作
    if(cmdList.at(0) == "mysql") {
        returnStr = "";
    }
    // 获取所有的用户名单
    else if(cmdList.at(0) == "getUsers") {
        QFile tempFile(tempDir.absolutePath()+"/User");
        if(tempFile.open(QIODevice::ReadOnly)) {
            // 读取并按行分割记录
            QString strAll      = tempFile.readAll();
            QStringList strList = strAll.split("\r\n");
            // 生成信息
            for(int i=0; i < strList.count(); i++) {
                QStringList tmpList = strList.at(i).split(" ");
                returnStr += tmpList.at(3);   // 生成名单
                if(i != strList.count()-1)  returnStr += " ";     // 生成str
            }
            // 清理
            strAll.clear();
            strList.clear();
        }
        tempFile.close();
    }

    // 获取所有的快递员信息名单
    else if(cmdList.at(0) == "getCouriers") {
        QFile tempFile(tempDir.absolutePath()+"/Courier");
        if(tempFile.open(QIODevice::ReadOnly)) {
            // 读取并按行分割记录
            QString strAll      = tempFile.readAll();
            QStringList strList = strAll.split("\r\n");
            // 生成信息
            for(int i=0; i < strList.count(); i++) {
                QStringList tmpList = strList.at(i).split(" ");
                returnStr += tmpList.at(3);   // 生成名单
                if(i != strList.count()-1)  returnStr += " ";     // 生成str
            }
            // 清理
            strAll.clear();
            strList.clear();
        }
        tempFile.close();
    }

    // 用户服务*****************************************************************************
    // 创建用户数据 ( cmd(0) + name + password + tel + address )____________________________________________
    else if(cmdList.at(0) == "user_insert") {
        QFile tempFile(tempDir.absolutePath()+"/User");     // 打开的文件
        if(tempFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
            // 获取注册账号
            QString strAll = tempFile.readAll();
            QTextStream output(&tempFile);   // 打开文件流并写入
            output.setCodec(QTextCodec::codecForName("utf-8"));

            // 没有用户
            if(strAll == "") {
                output << QString::number(1)+" "+cmdList.at(2)+" 0.000000 "+cmdList.at(1)+" "+cmdList.at(3)+" "+cmdList.at(4);
                returnStr = "1";  // 告诉账号
            } else {
                int count = 1;  // 一共多少条记录
                for(int i=0; i < strAll.size(); i++)
                    if(strAll[i] == '\n') count++;
                output << "\n"+QString::number(count+1)+" "+cmdList.at(2)+" 0.000000 "+cmdList.at(1)+" "+cmdList.at(3)+" "+cmdList.at(4);
                returnStr = QString::number(count+1); // 回账号
            }
        }
        else
            qDebug()<<"User File ERROR!";
        tempFile.close();
    }

    // 用户认证 (cmd(0) account password)________________________________________________________________________________
    else if(cmdList.at(0) == "user_identity") {
        returnStr = "fail";

        QFile tempFile(tempDir.absolutePath()+"/User");     // 打开的文件
        if(tempFile.open(QIODevice::ReadOnly)) {
            // 获取注册账号
            QString strAll      = tempFile.readAll();
            QStringList strList = strAll.split("\r\n"); // 一行信息
            // 逐行分析
            for(int i=0; i < strList.count(); i++) {
                // 分割单行
                QStringList tmpList = strList.at(i).split(" "); // 暂存行数据
                if( cmdList.at(1)==tmpList.at(0) && cmdList.at(2)==tmpList.at(1) ) {
                    // 登陆成功
                    returnStr = strList.at(i);  // 返回该行数据，方便创建用户
                    break;
                }
            }
            // 清理
            strAll.clear();
            strList.clear();
        }
        else
            qDebug()<<"User File ERROR!";
        tempFile.close();
    }

    // 更改用户数据（cmd account name password tel address）_________________________________________________
    else if(cmdList.at(0) == "user_update") {
        QFile tempFile(tempDir.absolutePath()+"/User");     // 打开的文件
        QString strAll;     // 全部信息
        QStringList strList;// 分割信息
        QStringList tmpList;// 暂存分割信息
        if(tempFile.open((QIODevice::ReadOnly|QIODevice::Text))) {
            QTextStream stream(&tempFile);  // 打开流，读出
            stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
            strAll=stream.readAll();
            strList=strAll.split('\n');
        }
        tempFile.close();

        // 写回信息
        tempFile.setFileName(tempDir.absolutePath()+"/User");
        if(tempFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
            QTextStream stream(&tempFile);  // 打开流，写入
            stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
            for(int i=0; i<strList.count(); i++) {
                // 分割单行
                tmpList = strList.at(i).split(" ");
                // 找到，修改
                if(cmdList.at(1).toInt() == tmpList.at(0).toInt()) {
                    // 规格化输入，%串忽略
                    stream << tmpList.at(0)+" ";    // account

                    if(cmdList.at(3) == "%")        // password
                        stream << tmpList.at(1)+" ";
                    else
                        stream << cmdList.at(3)+" ";

                    stream << tmpList.at(2)+" ";    // balance

                    if(cmdList.at(2) == "%")        // name
                        stream << tmpList.at(3)+" ";
                    else
                        stream << cmdList.at(2)+" ";

                    if(cmdList.at(4) == "%")        // tel
                        stream << tmpList.at(4)+" ";
                    else
                        stream << cmdList.at(4)+" ";

                    if(cmdList.at(5) == "%")        // address
                        stream << tmpList.at(5);
                    else
                        stream << cmdList.at(4);
                } else
                    stream << strList.at(i);
                if(i != strList.count()-1 ) stream << '\n';
            }
            // 清理
            strAll.clear();
            strList.clear();
        }
        tempFile.close();

        returnStr = "success";
    }

    // 用户钱数变化（cmd account double）____________________________________________________________________
    else if(cmdList.at(0) == "user_balanceChange") {
        QString strAll;     // 全部信息
        QStringList strList;// 分割信息
        QStringList tmpList;// 暂存分割信息
        // 读出信息
        QFile tempFile(tempDir.absolutePath()+"/User");
        if(tempFile.open((QIODevice::ReadOnly|QIODevice::Text))) {
            QTextStream stream(&tempFile);  // 打开流，读出
            stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
            strAll=stream.readAll();
            strList=strAll.split('\n');
        }
        tempFile.close();
        // 写回信息
        if(tempFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
            QTextStream stream(&tempFile);  // 打开流，写入
            stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
            for(int i=0; i<strList.count(); i++) {
                // 分割单行
                tmpList = strList.at(i).split(" ");
                if(cmdList.at(1).toInt() == tmpList.at(0).toInt()) {
                    stream << tmpList.at(0)+" "+tmpList.at(1)+" "+QString::number(tmpList.at(2).toDouble()+cmdList.at(2).toDouble(),'f',6)+" "
                              +tmpList.at(3)+" "+tmpList.at(4)+" "+tmpList.at(5);
                } else {
                    stream << strList.at(i);
                }
                if(i != strList.count()-1 ) stream << '\n';
            }
            // 清理
            strAll.clear();
            strList.clear();
        }
        tempFile.close();

        returnStr = "success";
    }

    // 快递员服务*****************************************************************************
    // 创建快递员数据  ( cmd(0) + name + password + tel + address )___________________________________________________
    else if(cmdList.at(0) == "courier_insert") {
        QFile tempFile(tempDir.absolutePath()+"/Courier");     // 打开的文件
        if(tempFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
            // 获取注册账号
            QString strAll = tempFile.readAll();
            QTextStream output(&tempFile);   // 打开文件流并写入
            output.setCodec(QTextCodec::codecForName("utf-8"));

            // 没有用户
            if(strAll == "") {
                output << QString::number(1)+" "+cmdList.at(2)+" 0.000000 "+cmdList.at(1)+" "+cmdList.at(3)+" "+cmdList.at(4);
                returnStr = "1";  // 告诉账号
            } else {
                int count = 1;  // 一共多少条记录
                for(int i=0; i < strAll.size(); i++)
                    if(strAll[i] == '\n') count++;
                output << "\n"+QString::number(count+1)+" "+cmdList.at(2)+" 0.000000 "+cmdList.at(1)+" "+cmdList.at(3)+" "+cmdList.at(4);
                returnStr = QString::number(count+1); // 回账号
            }
        }
        else
            qDebug()<<"User File ERROR!";
        tempFile.close();
    }

    // 快递员认证 (cmd(0) account password)___________________________________________________________________
    else if(cmdList.at(0) == "courier_identity") {
        returnStr = "fail";

        QFile tempFile(tempDir.absolutePath()+"/Courier");     // 打开的文件
        if(tempFile.open(QIODevice::ReadOnly)) {
            // 获取注册账号
            QString strAll      = tempFile.readAll();
            QStringList strList = strAll.split("\r\n"); // 一行信息
            // 逐行分析
            for(int i=0; i < strList.count(); i++) {
                // 分割单行
                QStringList tmpList = strList.at(i).split(" "); // 暂存行数据
                if( cmdList.at(1)==tmpList.at(0) && cmdList.at(2)==tmpList.at(1) ) {
                    // 登陆成功
                    returnStr = strList.at(i);  // 返回当前行，方便创建快递员
                    break;
                }
            }
            // 清理
            strAll.clear();
            strList.clear();
        }
        else
            qDebug()<<"User File ERROR!";
        tempFile.close();
    }

    // 快递员钱数变化 (cmd account double）__________________________________________________
    else if(cmdList.at(0) == "courier_balanceChange") {
        QString strAll;     // 全部信息
        QStringList strList;// 分割信息
        QStringList tmpList;// 暂存分割信息
        // 读出信息
        QFile tempFile(tempDir.absolutePath()+"/Courier");
        if(tempFile.open((QIODevice::ReadOnly|QIODevice::Text))) {
            QTextStream stream(&tempFile);  // 打开流，读出
            stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
            strAll=stream.readAll();
            strList=strAll.split('\n');
        }
        tempFile.close();
        // 写回信息
        if(tempFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
            QTextStream stream(&tempFile);  // 打开流，写入
            stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
            for(int i=0; i<strList.count(); i++) {
                // 分割单行
                tmpList = strList.at(i).split(" ");
                if(cmdList.at(1).toInt() == tmpList.at(0).toInt()) {
                    stream << tmpList.at(0)+" "+tmpList.at(1)+" "+QString::number(tmpList.at(2).toDouble()+cmdList.at(2).toDouble(),'f',6)+" "
                              +tmpList.at(3)+" "+tmpList.at(4)+" "+tmpList.at(5);
                } else {
                    stream << strList.at(i);
                }
                if(i != strList.count()-1 ) stream << '\n';
            }
            // 清理
            strAll.clear();
            strList.clear();
        }
        tempFile.close();

        returnStr = "success";
    }

    // 管理员服务*****************************************************************************
    // 管理员认证 (cmd(0) account password)__________________________________________________________
    else if(cmdList.at(0) == "admin_identity") {
        returnStr = "fail";

        QFile tempFile(tempDir.absolutePath()+"/Administrator");
        if(tempFile.open(QIODevice::ReadOnly)) {
            // 读取并按行分割记录
            QString strAll = tempFile.readAll();
            QStringList strList=strAll.split("\r\n");
            // 逐行分析
            for(int i=0; i < strList.count(); i++) {
                // 分割单行
                QStringList tmpList = strList.at(i).split(" ");
                if(cmdList.at(1).toInt() == tmpList.at(0).toInt() && cmdList.at(2) == tmpList.at(1)) {
                    returnStr = strList.at(i);
                    break;
                }
            }
            // 清理
            strAll.clear();
            strList.clear();
        }
        else
            qDebug()<<"Administrator File ERROR!";
        tempFile.close();
    }

    // 管理员钱数变化(cmd(0), double) _________________________________________________________________
    else if(cmdList.at(0) == "admin_balanceChange") {
        QString strAll;     // 全部信息
        QStringList strList;// 分割信息
        QStringList tmpList;// 暂存分割信息
        // 读出信息
        QFile tempFile(tempDir.absolutePath()+"/Administrator");
        if(tempFile.open((QIODevice::ReadOnly|QIODevice::Text))) {
            QTextStream stream(&tempFile);  // 打开流，读出
            stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
            strAll=stream.readAll();
            strList=strAll.split('\n');
        }
        tempFile.close();
        // 写回信息
        tempFile.setFileName(tempDir.absolutePath()+"/Administrator");
        if(tempFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
            QTextStream stream(&tempFile);  // 打开流，写入
            stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
            // 写第一行
            tmpList = strList.at(0).split(" ");
            stream << tmpList.at(0)+" "+tmpList.at(1)+" "+QString::number(cmdList.at(1).toDouble()+tmpList.at(2).toDouble(),'f',6)+" "
                      +tmpList.at(3)+" "+tmpList.at(4)+"\n";
            // 写后面的
            for(int i=1; i < strList.count(); i++) {
                stream << strList.at(i);
                if(i != strList.count()-1 ) stream << '\n';
            }
            // 清理
            strAll.clear();
            strList.clear();
        }
        tempFile.close();

        returnStr = "success";
    }

    // 管理员查询所有用户 _____________________________________________________________________________
    else if(cmdList.at(0) == "admin_findUsers") {
        QFile tempFile(tempDir.absolutePath()+"/User");
        if(tempFile.open(QIODevice::ReadOnly)) {
            // 读取并按行分割记录
            QString strAll = tempFile.readAll();
            QStringList strList=strAll.split("\r\n");
            // 生成串
            for(int i=0; i<strList.count()-1; i++)
                returnStr += strList.at(i)+"|";
            returnStr += strList.at(strList.count()-1);
            // 清理
            strAll.clear();
            strList.clear();
        }
        tempFile.close();
    }
    
    // 管理员删除快递员
    else if(cmdList.at(0) == "admin_deleteCourier") {
		QString strAll;     // 全部信息
		QStringList strList;// 分割信息
		QStringList tmpList;// 暂存分割信息

		// 读出信息
		QFile tempFile(tempDir.absolutePath()+"/Courier");
		if(tempFile.open((QIODevice::ReadOnly|QIODevice::Text))) {
			QTextStream stream(&tempFile);  // 打开流，读出
			stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
			strAll=stream.readAll();
			strList=strAll.split('\n');
		}
		tempFile.close();

		// 写回信息
		tempFile.setFileName(tempDir.absolutePath()+"/Courier");
		if(tempFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
			QTextStream stream(&tempFile);  // 打开流，写入
			stream.setCodec(QTextCodec::codecForName("utf-8")); // 规定utf8
			for(int i=0; i<strList.count(); i++) {
				// 分割单行
				tmpList = strList.at(i).split(" ");
				// 找到，修改
                if(cmdList.at(1).toInt() == tmpList.at(0).toInt()) {
					stream << tmpList.at(0)+" " << tmpList.at(1)+" " << tmpList.at(2)+" "
						   << tmpList.at(3)+"(deleted) " << tmpList.at(4)+" " << tmpList.at(5);
				} else
					stream << strList.at(i);
				if(i != strList.count()-1 ) stream << '\n';
			}
			// 清理
			strAll.clear();
			strList.clear();
		}
		tempFile.close();
		
		returnStr = "success";
    }

    // 返回信息
    array = returnStr.toUtf8();
    threadSocket->write(array);
    qDebug() << "server: "+array;
}
