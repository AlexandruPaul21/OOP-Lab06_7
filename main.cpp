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
    FileRepo* repo=new FileRepo{"data.txt"};
    Validator valid;
    Service srv{repo,valid};

    Console master=Console(srv);
    master.show_ui();
    delete repo;
    return 0;
}
