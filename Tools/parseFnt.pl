use strict;

if ($#ARGV < 0)
{
	die "Usage: perl parseFnt.pl <fnt file>\n";
}

open FILE, '<', $ARGV[0] or die $!;

print '<?xml version="1.0" encoding="ISO-8859-1"?>' . "\n";
foreach (<FILE>)
{
	if ($_ =~ m/^page\s*id=\d*\s*file=\"(\w*\.\w*)\"/gi)
	{
		print '<Font file="Resources/Fonts/' . $1 . '">' . "\n";
	}
	
	if ($_ =~ m/^char\s*id=(\d*)\s*x=(\d*)\s*y=(\d*)\s*width=(\d*)\s*height=(\d*)\s*xoffset=(-?)(\d*)\s*yoffset=(-?)(\d*)\s*xadvance=(\d*)/gi)
	{
		print "\t" . '<Character x="' . $2 . '" y="' . $3 . '" width="' . $4 . '" height="' . $5 . '" x-offset="' . $6 . $7 . '" y-offset="' . $8 . $9 .'" x-advance="' . $10 . '">' . $1 . '</Character>' . "\n";
	}
}
print '</Font>' . "\n";