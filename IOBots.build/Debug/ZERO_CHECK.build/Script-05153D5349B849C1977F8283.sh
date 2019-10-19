#!/bin/sh
make -C /Users/aaron/iobots -f /Users/aaron/iobots/CMakeScripts/ZERO_CHECK_cmakeRulesBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
