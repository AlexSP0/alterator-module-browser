#include "mainwindow.h"

#include <QApplication>
#include <QStandardItemModel>
#include <QTranslator>

#include "model/aclocalapllicationmodelbuilder.h"
#include "model/acobjectsmodelbuilder.h"
#include "modelbuilder.h"
#include "accontroller.h"
#include "model/acmodel.h"


const QString DBUS_SERVICE_NAME                 = "ru.basealt.alterator";
const QString DBUS_PATH                         = "/ru/basealt/alterator";
const QString DBUS_FIND_INTERFACE_NAME          = "ru.basealt.alterator.application";
const QString DBUS_MANAGER_INTERFACE_NAME       = "ru.basealt.alterator.manager";
const QString GET_OBJECTS_METHOD_NAME           = "get_objects";
const QString INFO_METHOD_NAME_FOR_ACOBJECT     = "info";
const QString CATEGORY_METHOD_NAME_FOR_ACOBJECT = "category";

const QString DBUS_LOCAL_APP_PATH              = "/ru/basealt/alterator/module_finder";
const QString DBUS_LOCAL_APP_INTERFACE_NAME    = "ru.basealt.alterator.finder";
const QString DBUS_LOCAL_APP_GET_LIST_OF_FILES = "list";
const QString DBUS_LOCAL_APP_GET_DESKTOP_FILE  = "file";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLocale locale;
    QTranslator translator;
    QString language = locale.system().name().split("_").at(0);
    translator.load(language, ".");
    a.installTranslator(&translator);

    ACLocalApllicationModelBuilder appModelBuilder(DBUS_SERVICE_NAME,
                                                   DBUS_LOCAL_APP_PATH,
                                                   DBUS_LOCAL_APP_INTERFACE_NAME,
                                                   DBUS_LOCAL_APP_GET_LIST_OF_FILES,
                                                   DBUS_LOCAL_APP_GET_DESKTOP_FILE);

    std::unique_ptr<ACLocalApplicationModel> appModel = appModelBuilder.buildModel();

    ACObjectsModelBuilder objectModelBuilder(DBUS_SERVICE_NAME,
                                             DBUS_PATH,
                                             DBUS_MANAGER_INTERFACE_NAME,
                                             DBUS_FIND_INTERFACE_NAME,
                                             GET_OBJECTS_METHOD_NAME,
                                             INFO_METHOD_NAME_FOR_ACOBJECT,
                                             CATEGORY_METHOD_NAME_FOR_ACOBJECT);

    std::unique_ptr<ACModel> model = objectModelBuilder.buildModel();
    model->translateModel(QString("ru"));
    MainWindow w;
    ACController controller(&w, model.get());
    w.setController(&controller);

    w.show();
    return a.exec();
}
