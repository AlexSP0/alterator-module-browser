#ifndef AB_CONTROLLER_H
#define AB_CONTROLLER_H

#include "../aobuilder/objects/localappobject.h"
#include "model/model.h"
#include "pushbutton.h"

#include <utility>

#include <QObject>
#include <QPushButton>
#include <QStandardItemModel>

namespace ab
{
class CategoryWidget;
class MainWindow;

class ControllerPrivate;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(MainWindow *w, std::unique_ptr<model::Model> m, QObject *parent = nullptr);
    ~Controller();

private:
    void translateModel();

public:
    Controller(const Controller &) = delete;
    Controller(Controller &&)      = delete;
    Controller &operator=(const Controller &) = delete;
    Controller &operator=(Controller &&) = delete;

public slots:
    void moduleClicked(ao_builder::LegacyObject obj);
    //    void onInterfaceClicked(ao_builder::LocalAppObject *app);
    //    void onDBusStructureUpdate(QString service, QString prev, QString next);

private:
    ControllerPrivate *d;
};
} // namespace ab

#endif // AB_CONTROLLER_H
