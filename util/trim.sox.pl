#!/usr/bin/perl

use Cwd;

chdir $ARGV[0] or die if $ARGV[0];

while (<STDIN>) {

  if (/^Session:(.*)/){ $session = $1 };

  if (/^User:(.*)/){ $user = $1 };

  if (/^totalRoundtripMs:(.*)/){ $seconds = $1 * 0.001 };

  if (($session) and ($user) and ($seconds)){

    $cwd = getcwd();

    $file, $user =~ s/[#@,;:<>*^|?\\\/]//g;

    $file = "$session-${user}";

    chdir "$session" or die;

    system "sox -S '${file}.wav' '${file}.trimmed.wav' trim ${seconds}";

    $session, $user, $seconds = "";
    chdir $cwd or die;

  }

}
