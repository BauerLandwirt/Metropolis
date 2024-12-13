numberOfBars=70.0
minDom = 0.0
maxDom = 5.0
widthOfBars = (maxDom-minDom)/numberOfBars
hist(x,widthOfBars)=widthOfBars*floor(x/widthOfBars)+widthOfBars/2.0
set xrange [minDom:maxDom]
set xlabel "x" font "Times-Roman,12"
set boxwidth widthOfBars
set ylabel "frequency" font "Times-Roman,12"
set title "Histogram for generated Metropolis-samples"
set style fill solid 0.3 border
set terminal pdf
set output "MetropolisPlotExample.pdf"
plot "MetropolisSample.txt" u (hist($1,widthOfBars)):(1.0) smooth freq w boxes lc rgb"blue" notitle
