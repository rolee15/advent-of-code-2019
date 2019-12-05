#!/usr/bin/perl

use strict;

print "Henlo fren!\n";

my $from = "138307";
my $to = "654504";
my @results = ();

for (my $number = $from; $number < $to; $number++)
{
	my @arr = split //, $number;
	
	# Flags
	my $double_flag = 0;
	my $good_flag = 1;
	my $two_in_a_row = 0;
	my $large_group = 0;
	my $str = "";

	$str = $str . "$number: ";
	my $last = -1;
	for my $digit (@arr)
	{
		if ($last != -1)
		{
			$str = $str . "$digit ";
			# Always check if digits are decreasing
			if ($last > $digit)
			{
				$good_flag = 0;
			}
			
			# Check if same
			if ($last == $digit)
			{
				# If same digit and had double, large group
				if ($two_in_a_row)
				{
					$str = $str . "ld ";
					$large_group = 1;
				}
				else
				{
					$str = $str . "dd ";
					$two_in_a_row = 1;
				}
			}
			else
			{
				# Change in digit, check if double or large group
				if ($two_in_a_row and !$large_group)
				{
					$two_in_a_row = 0;
					$double_flag = 1;
				}
				else
				{
					$two_in_a_row = 0;
					$large_group = 0;
				}
				
				$str = $str . "ch ";
			}
		}
		$last = $digit;
	}
	
	# After loop check for last double digits
	$double_flag = 1 if ($two_in_a_row and !$large_group);
	
	$str = $str . "$good_flag $double_flag $large_group ";
	print $str if $good_flag;
	print " Good" if $good_flag and $double_flag;
	print "\n" if $good_flag;
	push @results, $number if $good_flag and $double_flag;
}

print "Suitable passwords:\n";

my $length = @results;
print "$length\n";

