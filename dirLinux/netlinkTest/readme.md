# **This is a test folder for netlink**
1. 对于从user to kernel的通讯，driver必须先向内核注册一个struct genl_family，并且注册一些cmd的处理函数。这些cmd是跟某个family关联起来的。注册family的时候我们可以让内核自动为这个family分配一个ID。每个family都有一个唯一的ID，其中ID号0x10是被内核的nlctrl family所使用。当注册成功以后，如果user program向某个family发送cmd，那么内核就会回调对应cmd的处理函数。对于user program，使用前，除了要创建一个socket并绑定地址以外，还需要先通过family的名字获取family的ID。获取方法，就是向nlctrl这个family查询。详细的方法可以看后面的例子。有了family的ID以后，才能向该family发送cmd。

2. 对于从kernel to user的通讯，采用的是广播的形式，只要user program监听了，都能收到。但是同样的，user program在监听前，也必须先查询到family的ID。

## **Case 1**: *genericNetlink1*
- user到kernel，user program通过发送一个命令到内核，内核相应的模块接收到命令以后，执行对应的回调函数

## **Case 2**: *genericNetlink2*
- kernel到user，user program先创建一个socket并监听，内核发生某个事件以后，就可以发送一个广播，通知user program


## **References**
1. https://blog.csdn.net/ty3219/article/details/63683698
1. https://blog.csdn.net/yldfree/article/details/82593873
1. https://blog.csdn.net/clytiejoe/article/details/70666679
1. https://www.infradead.org/~tgr/libnl/doc/core.html
1. https://markdown.com.cn/basic-syntax/lists.html