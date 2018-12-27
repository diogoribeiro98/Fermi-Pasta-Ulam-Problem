
data <- read.table('pos_data.txt')

# 3 figures arranged in 3 rows and 1 column
#attach(mtcars)
par(mfrow=c(1,3))
hist(data[133:394,4]^2,freq=TRUE,breaks="Sturges",xlim=c(0,1),col="blue",xlab=expression('q'^'2'),main=" t = 3 s")
hist(data[65605:65866,4]^2,freq=TRUE,breaks="Sturges",xlim=c(0,0.0012),col="blue",xlab=expression('q'^'2'),main="t = 10^3")
#hist(data[34000-2:34000,4]^2,freq=TRUE,breaks="Sturges",xlim=c(0,0.02),col="blue",xlab=expression('q'^'2'),main="Square Velocity distribuition")
hist(data[116293:116554,4]^2,freq=TRUE,breaks="Sturges",xlim=c(0,0.001),col="blue",xlab=expression('q'^'2'),main="t = 10^6")
