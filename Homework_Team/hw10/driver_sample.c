#include <linux/init.h> //module_init, module_exit 매크로 정의
#include <linux/kernel.h> // printk 함수 정의
#include <linux/module.h>//모듈 관련 자료 구조 및 매크로 정의
// (~/ecube/linux_kernel/include/…)
int __init init_hello(void) //__init: optional 쓰면 좋고 안써도 됨
{
printk("Hello world.\n");
return 0;
}
void __exit exit_hello(void) //__exit: optional
{
printk("Good-bye~ \n");
}
module_init(init_hello); // 􀀀 모듈 로딩시 해당 함수 호출
module_exit(exit_hello); // 􀀀 모듈 제거시 해당 함수 호출
MODULE_LICENSE("GPL");
