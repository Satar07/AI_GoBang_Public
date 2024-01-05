#include "Application.h"

int main() {
    Instrumentor::Get().BeginSession();
    Application::main();
    Instrumentor::Get().EndSession();
}
