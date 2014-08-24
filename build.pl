#!/usr/local/bin/perl

use File::Copy;

sub help_and_exit{
    print "Usage: build.pl paper|presentation\n";
    exit;
}

$num_args = $#ARGV + 1;
if($num_args!=1) {
    help_and_exit();
}

$target=$ARGV[0];
if($target eq "paper"){
    system("gnuplot msswarp.gnuplot");
    chdir "paper/";
    system("pdflatex -shell-escape GAME_HARD_01.tex");
    system("bibtex web.aux");
    system("bibtex GAME_HARD_01.aux");
    system("pdflatex -shell-escape GAME_HARD_01.tex");
    system("pdflatex -shell-escape GAME_HARD_01.tex");
    copy("GAME_HARD_01.pdf", "../GAME_HARD_01.pdf") or die "Failed to copy: $!";
} elsif($target eq "presentation"){
    chdir "presentation/";
    system("pdflatex GAME_HARD_01_PRESENTATION.tex");
    system("pdflatex GAME_HARD_01_PRESENTATION.tex");
    copy("GAME_HARD_01_PRESENTATION.pdf", "../GAME_HARD_01_PRESENTATION.pdf")
        or die "Failed to copy: $!";
} else{
    help_and_exit();
}
