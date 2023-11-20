#include <linux/init.h> //module_init, module_exit 매크로 정의
#include <linux/kernel.h> // printk 함수 정의
#include <linux/module.h>//모듈 관련 자료 구조 및 매크로 정의
#include <linux/fs.h> // register_chrdev 함수
#include <asm/uaccess.h> // copy_to_user함수

#define HELLO_MAJOR_NUM 290
#define HELLO_NAME "hello"

static int hello_open(struct inode *node, struct file *pfile)
{
printk("hello_open enter\n");
return 0;
}

static ssize_t hello_read(struct file *pfile, char __user *pBuff, size_t size, loff_t *filepos)
{
char arrData[4] = {'1','2','3','4'};
printk("hello_read enter\n");
if ( size >= 4)
{
copy_to_user( pBuff, arrData, 4 );
//put_user (i, pBuff); //i 변수값을 pBuff 사용자 메모리값에 대입
return 4;
}
//pfile->f_flags 를 읽어보면 open시 줬던 옵션값을 읽힘: O_NONBLOCK 등
return 0;
}

static ssize_t hello_write(struct file *pfile, const char __user *pBuff, size_t size, loff_t *filepos) {
char arrData[4];
printk("hello_write enter\n");
if( size >= 4 )
{ copy_from_user ( arrData , pBuff , 4 );
//get_user ( i, pBuff ); //i변수에 pBuff의 값을 대입한다.
return 4; }
return 0;
}

static int hello_release(struct inode *node, struct file *pfile)
{ printk("hello_release enter\n");
return 0;
}

static const struct file_operations hello_fops = {
.owner = THIS_MODULE,
.open = hello_open,
.read = hello_read,
.write = hello_write,
.release = hello_release,
};

int flagRegisterSuccess = 0;

int __init init_hello(void)
{ int ret;
printk("Hello world.\n");
ret = register_chrdev(HELLO_MAJOR_NUM, HELLO_NAME, &hello_fops);
if ( ret < 0)
{ printk("Hello registr_chrdev fail\n");
return ret; }
flagRegisterSuccess = 1;
return 0;
}

void __exit exit_hello(void)
{ if ( flagRegisterSuccess)
{ flagRegisterSuccess = 0;
unregister_chrdev(HELLO_MAJOR_NUM, HELLO_NAME);
}
printk("Good-bye~ \n");
}

module_init(init_hello); // 모듈 로딩시(insmod) 해당 함수 호출
module_exit(exit_hello); // 모듈 제거시(rmmod) 해당 함수 호출
MODULE_LICENSE("GPL");