
#include "server/Server.h"
using namespace boot;
using namespace std;

int main(int argc, char* argsv[]) {
    /** CacheManagerTest
    CacheManager<string,string>* cm = new FileCacheManager<string, string>();
    cm->insert("idan","nadi");
    cm->insert("nili","ilin");
    cm->insert("yogev","vegoy");
    std::cout << cm->get("idan") << std::endl;*/
    Main* m = new Main();
    m->main(argc, argsv);
    return 0;
}
