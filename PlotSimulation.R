#!/usr/bin/env Rscript

options(stringsAsFactors=F)
args = commandArgs(T)
fname = args[1]
t1 = read.delim(gzfile(fname),header=F)
times = t1[,1]
fixation.times = c()
initial.frequency = c()
trajs = matrix(ncol=0,nrow=nrow(t1))
for (n in 2:ncol(t1)) {
    m = matrix(as.numeric(unlist(strsplit(t1[,n],"|",fixed=T))),nrow=nrow(t1),byrow=T)
    gen.size = ncol(m)
    trajs = cbind(trajs,m)
    tf = min(c(which(apply(m,1,max)==1),nrow(m)+1))
    if (tf <= nrow(m)) {
        fixation.times = c(fixation.times,times[tf])
        initial.frequency = c(initial.frequency,m[1,which(m[tf,] == 1)[1]])
    } else {
        fixation.times = c(fixation.times,NA)
        initial.frequency = c(initial.frequency,NA)
    }
}
nrep = min(7,ncol(trajs)/gen.size)
par(mfrow=c(2,1),lty=1,lwd=2,pch=20,las=1,mar=c(5,5,1,1))
matplot(times,trajs[,1:(gen.size*nrep)],t='l',ylim=c(0,1),lty=1,col=1:2,
        xlab="Generations",ylab="Frequency")
points(fixation.times[1:nrep],initial.frequency[1:nrep],pch=20,col=4,cex=1.5)

fbr = 0:50/50
s1 = seq(1,ncol(trajs),by=2)
s2 = seq(2,ncol(trajs),by=2)
tmax = times[length(times)]
step = min(15,as.integer(.5+tmax/4))
tlim = min(tmax,300)
h = hist(trajs[1,s1], plot=F, br=fbr)
plot(h$dens, h$mids, t='l', xlim=c(0,tlim),
     ylab="Frequency", xlab="Generation")
h = hist(trajs[1,s2], plot=F, br=fbr)
lines(h$dens, h$mids, col='red')
for (yp in seq(step,tlim,by=step)) {
    h = hist(trajs[yp,s1], plot=F, br=fbr)
    lines(yp+h$dens, h$mids)
    h = hist(trajs[yp,s2], plot=F, br=fbr)
    lines(yp+h$dens, h$mids, col='red')
}
