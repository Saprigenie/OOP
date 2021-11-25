#include <QApplication>

#include "Game/Game.h"
#include "Logic/Rule/DestroyedObjectNumRule.h"
#include "Logic/Rule/DestroyObjectRule.h"
#include "Logic/Rule/KeyItemRule.h"
#include "Logic/Rule/RulesList.h"

static RulesList all_rules = RulesList();

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Game<all_rules> game;
    all_rules.AddRule(new DestroyedObjectNumRule<2, 1, 2>());
    all_rules.AddRule(new KeyItemRule<1, 2, 4>());
    all_rules.AddRule(new KeyItemRule<1, 6, 4>());
    all_rules.AddRule(new DestroyObjectRule<3, 1, 1>());
    game.Start();
    return a.exec();
}
