#!/usr/bin/perl
use 5.16.0;
use warnings FATAL => 'all';

use Test::Simple tests => 3;

use Expect;

# If you want to see stdout, during
# tests for debugging, you can comment this out.
# $Expect::Log_Stdout = 0;

my $TO = 10;
my ($good, $text);

system(qq{make});

my $tty = Expect->spawn(qq{timeout -k 60 55 make qemu});
$tty->expect($TO, "init: starting sh");
sleep(1);

# Shell Script to create some directories from the main shell and call sub shell
$tty->send("sh test6.sh\n");
$tty->expect($TO, "test complete");

# Script to Change directory (cd) from sub shell, print the current directory path (pwd) and exit
$tty->send("sub test7.sh\n");
$tty->expect($TO, "test complete");

# Now we'll be back into the main shell, so if we try printing the working directory, it will be the root directory (before calling subshell).
# So, changes made in subshell is not carried over to main shell
$tty->send("/pwd \n");
$tty->expect($TO, "test complete");

sleep(5);
$tty->send("halt\n");
sleep(1);
