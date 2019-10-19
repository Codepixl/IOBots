# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.IOBots.Debug:
/Users/aaron/iobots/Debug/IOBots:
	/bin/rm -f /Users/aaron/iobots/Debug/IOBots


PostBuild.IOBots.Release:
/Users/aaron/iobots/Release/IOBots:
	/bin/rm -f /Users/aaron/iobots/Release/IOBots


PostBuild.IOBots.MinSizeRel:
/Users/aaron/iobots/MinSizeRel/IOBots:
	/bin/rm -f /Users/aaron/iobots/MinSizeRel/IOBots


PostBuild.IOBots.RelWithDebInfo:
/Users/aaron/iobots/RelWithDebInfo/IOBots:
	/bin/rm -f /Users/aaron/iobots/RelWithDebInfo/IOBots




# For each target create a dummy ruleso the target does not have to exist
