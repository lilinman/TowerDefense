# TowerDefense
今天完成大工程，把地图和窗口还有图片的比例尺寸改了，这时候才意识到const全局变量的重大意义。
把原来的object和BaseTower都改成了抽象类，新增了不同类型的防御塔Tower123来做派生类，语法不过关报错真是差点要了我的命，
破口大骂，被迫深刻认识了虚函数抽象类的用法。
实现防御塔升级功能和删除防御塔功能的时候，在删除防御塔的时候程序一直会异常结束，非常无语，差点就想上课堂派求助，之后用了
一两个小时小时，用qDebug解决了，丧心病狂在每一个函数下面都用了qdebug输出，最后锁定在循环检查防御塔的函数里面，再细一点，
发现没有执行完循环，vector的erase已经执行完毕，问题出现在vector的迭代上，因为根据判断我要删除的是最后一个，而erase执行
之后，auto自动变成了vector.end()，而for循环里判断的是auto不等于vector.end()就会中止，这也就解释了原来我的最后一个怪物
死亡或者走到终点程序就会异常中止，惊天大坑，在最后判断一下如果等于最后一个位置break就可以解决bug。
