#
#
-include Template\make\Makefile

test:
	@echo test
	@echo Module path: $($(MODULE_NAME)_MODULE_PATH)
	@echo C-Files: $(CC_FILES)
	@echo CPP-Files: $(CPP_FILES)
	@echo Include directories: $(CC_INCLUDE)