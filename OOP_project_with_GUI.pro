QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Gui/DrawObject/DrawableObject.cpp \
    Gui/GameView.cpp \
    Gui/View/Observable.cpp \
    Logging/Log/Log.cpp \
    Logging/Log/LogConsole.cpp \
    Logging/Log/LogFile.cpp \
    Logging/Loggable/Loggable.cpp \
    Logging/Logger/Logger.cpp \
    Logic/Cell/Cell.cpp \
    Logic/Cell/CellTypes/EntranceCell.cpp \
    Logic/Cell/CellTypes/ExitCell.cpp \
    Logic/Cell/CellTypes/PassableCell.cpp \
    Logic/Cell/CellTypes/PathlessCell.cpp \
    Logic/Controller/Controller.cpp \
    Logic/GameLogic.cpp \
    Logic/PlaceableInCell/Enemies/Enemy.cpp \
    Logic/PlaceableInCell/Enemies/ImmortalEnemy.cpp \
    Logic/PlaceableInCell/Enemies/LimitedLifeEnemy.cpp \
    Logic/PlaceableInCell/Enemies/MoveStrategies/MoveStrategyChase.cpp \
    Logic/PlaceableInCell/Enemies/MoveStrategies/MoveStrategyConfusion.cpp \
    Logic/PlaceableInCell/Enemies/MoveStrategies/MoveStrategyStandart.cpp \
    Logic/PlaceableInCell/Furniture/Furniture.cpp \
    Logic/PlaceableInCell/Items/DamageToEnemiesItem.cpp \
    Logic/PlaceableInCell/Items/Item.cpp \
    Logic/PlaceableInCell/Items/KeyItem.cpp \
    Logic/PlaceableInCell/Items/SanityAffectItem.cpp \
    Logic/PlaceableInCell/PlaceableInCell.cpp \
    Logic/PlaceableInCell/Player/Player.cpp \
    Logic/Room/Room.cpp \
    Logic/Rule/RulesList.cpp \
    main.cpp

HEADERS += \
    Game/ControllerObserver/ControllerObserver.h \
    Game/Game.h \
    Game/RoomChangeNotify/RoomChangeObserver.h \
    Game/RoomState.h \
    Gui/DrawObject/DrawableObject.h \
    Gui/GameView.h \
    Gui/View/Observable.h \
    Gui/View/Observer.h \
    Logging/Log/Log.h \
    Logging/Log/LogConsole.h \
    Logging/Log/LogFile.h \
    Logging/Loggable/Loggable.h \
    Logging/Logger/Logger.h \
    Logging/UtilityEnums/LogMode.h \
    Logging/UtilityEnums/LogStyle.h \
    Logic/Cell/Cell.h \
    Logic/Cell/CellTypes/EntranceCell.h \
    Logic/Cell/CellTypes/ExitCell.h \
    Logic/Cell/CellTypes/PassableCell.h \
    Logic/Cell/CellTypes/PathlessCell.h \
    Logic/Controller/Controller.h \
    Logic/GameLogic.h \
    Logic/PlaceableInCell/Enemies/Enemy.h \
    Logic/PlaceableInCell/Enemies/ImmortalEnemy.h \
    Logic/PlaceableInCell/Enemies/LimitedLifeEnemy.h \
    Logic/PlaceableInCell/Enemies/MoveStrategies/MoveStrategy.h \
    Logic/PlaceableInCell/Enemies/MoveStrategies/MoveStrategyChase.h \
    Logic/PlaceableInCell/Enemies/MoveStrategies/MoveStrategyConfusion.h \
    Logic/PlaceableInCell/Enemies/MoveStrategies/MoveStrategyStandart.h \
    Logic/PlaceableInCell/Enemies/MoveStrategies/StrategiesEnum.h \
    Logic/PlaceableInCell/Furniture/Furniture.h \
    Logic/PlaceableInCell/InteractionEnum.h \
    Logic/PlaceableInCell/Items/DamageToEnemiesItem.h \
    Logic/PlaceableInCell/Items/Item.h \
    Logic/PlaceableInCell/Items/KeyItem.h \
    Logic/PlaceableInCell/Items/SanityAffectItem.h \
    Logic/PlaceableInCell/PlaceableInCell.h \
    Logic/PlaceableInCell/PlaceablesDeclaration.h \
    Logic/PlaceableInCell/Player/Player.h \
    Logic/Room/Pos.h \
    Logic/Room/Room.h \
    Logic/Rule/DestroyObjectRule.h \
    Logic/Rule/DestroyedObjectNumRule.h \
    Logic/Rule/KeyItemRule.h \
    Logic/Rule/Rule.h \
    Logic/Rule/RulesList.h \
    Logic/Rule/TemplateRule.h

FORMS += \
    Gui/GameView.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    data.qrc
