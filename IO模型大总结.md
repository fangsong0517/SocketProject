# IO模型大总结

## 直接循环

![image.png](http://ww1.sinaimg.cn/large/006Uqzbtly1gfjovmg2jmj30vv0h3dkv.jpg)

基于fork对进程

## **reactor dispatch(反应堆调度)**

![image.png](http://ww1.sinaimg.cn/large/006Uqzbtly1gfjp3ap54rj30sy0i2dlb.jpg)

## **带线程池的反应堆**

![image.png](http://ww1.sinaimg.cn/large/006Uqzbtly1gfjp7papk3j30lj0ikwjs.jpg)



## **主从模式的反应堆**

![image.png](http://ww1.sinaimg.cn/large/006Uqzbtly1gfjpc7aewlj30k00ietg2.jpg)

reactor dispatch反应堆调度

Acceptor受体

Main Accpet thread主接受线程

sub-reactor thread子反应器线程

worker threads工作线程

Thread Pool线程池

## **主从线程池的反应堆**

![image.png](http://ww1.sinaimg.cn/large/006Uqzbtly1gfjpgdcgcfj30cq0ik0z5.jpg)

reactor dispatch反应堆调度

Acceptor受体

Main Accpet thread主接受线程

sub-reactor thread子反应器线程

worker threads工作线程

Thread Pool线程池



