#ifndef APP_MENU_HPP
#define APP_MENU_HPP

namespace UI {

class AppMenu {
public:
    // Launches the interactive multi-tiered CLI menu system
    static void run();

private:
    // Sub-menus
    static void runDSAWorkbench();
    static void runMolecularBiology();
    static void runTransformationsAndSearch();
    static void runComparisonAndSorting();
    static void runGraphAnalytics();

    // DSA Workbench Specific Actions
    static void runDynamicArrayDemo();
    static void runUndoRedoDemo();
    static void runRNAValidatorDemo();
    static void runSlidingWindowDemo();
    static void runRestrictionSiteDemo();
};

} // namespace UI

#endif // APP_MENU_HPP
