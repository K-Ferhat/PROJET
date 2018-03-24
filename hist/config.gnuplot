set term jpeg
set xrange [0:255]
set yrange [0:]

set output "hist/input.jpg"
set title "Input histogram"
plot 'hist/input_hist.data' with boxes

set output "hist/output.jpg"
set title "Output histogram"
plot 'hist/output_hist.data' with boxes
