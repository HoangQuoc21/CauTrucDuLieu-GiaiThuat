# Bai 4

dt11 = read.csv("data11.csv",header=T)
dt11
attach(dt11)
a
b
n

mysummary = function(){
	x = rep((a+b)/2,n)
	result = c(mean(x),var(x),min(x),max(x))
	return(result)
}
mysummary()

?plot

k = 0:8;
p = function(k) choose(8,k) * 0.3^k * 0.7^(8-k);
p(k)

f = function(x, mu=0, sigma=1){
1/sqrt(2*pi*sigma^2) * exp(-(x-mu)^2/(2*sigma^2))
}

F = function(k) sum(p(0:k))
F(4)
F(5)
F(4:5)
F = Vectorize(F)

F2 = function(a,mu = 0, sigma = 1){
integrate(function(x) f(x,mu,sigma), lower = -Inf, upper =
a)$value
}
F2 = Vectorize(F2)
F2(1.96)


