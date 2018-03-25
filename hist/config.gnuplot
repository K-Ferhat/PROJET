set term jpeg
set xrange [0:255]
set yrange [0:]
set style data boxes
unset key

set xlabel 'Pixel value'
set ylabel 'Num of pixels'

#input.jpg
set output "hist/input.jpg"
set title "Input histogram"
plot 'hist/input_hist.data'

#output.jpg
set output "hist/output.jpg"
set title "Output histogram"
plot 'hist/output_hist.data'

#compare.jpg
set output "hist/compare.jpg"
set multiplot layout 2, 1 title "Input vs outut histogram" 

set lmargin 12
unset title

unset xlabel
plot 'hist/input_hist.data'

set xtics
set xlabel 'Pixel value'
plot 'hist/output_hist.data'

unset multiplot
