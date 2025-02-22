#ifndef MODULE_H
#define MODULE_H

// Function prototypes for module management
void init_module(const char *module_name);
void load_module(const char *module_name);
void update_module(const char *module_name);
void unload_module(const char *module_name);

#endif // MODULE_H
