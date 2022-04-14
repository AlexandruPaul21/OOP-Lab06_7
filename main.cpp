#include "service.h"
#include "repo.h"
#include "domain.h"
#include "UI.h"
#include "tests.h"

/**
 * Master
 * @return 0
 */
int main() {
    //test_all();
    Repo repo;
    Validator valid;
    Service srv{repo,valid};

    Console master=Console(srv);
    master.show_ui();
    return 0;
}
