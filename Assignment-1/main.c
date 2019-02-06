#include <linux/module.h>
#include <linux/version.h>
//#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
 

#include <linux/uaccess.h>
#include <linux/moduleparam.h>
#include <linux/random.h>


static dev_t first; // Global variable for the first device number 
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class

char in[100];
char ch[3]={'x','y','z'};
char out[100];

int i,p,m;





static int my_open(struct inode *i, struct file *f)
{
  printk(KERN_INFO "Driver: open()\n");
  return 0;
}
  static int my_close(struct inode *i, struct file *f)
{
  printk(KERN_INFO "Driver: close()\n");
  return 0;
}
  static ssize_t my_read(struct file *f, char __user *buf, size_t
  len, loff_t *off)
{
unsigned long ret;

unsigned int k=0;
unsigned int rem=0;
get_random_bytes(&k,sizeof(int));


printk(KERN_INFO "Driver: read()\n");
for(m=0;m<10;m++){
rem = k % 10;
k=k/10;
out[m]=rem;
}
ret=copy_to_user(buf,out,len);
return ret;
}
  
  static struct file_operations fops =
{
  .owner = THIS_MODULE,
  .open = my_open,
  .release = my_close,
  .read = my_read,
  
};
 
static int __init ofcd_init(void) /* Constructor */
{
  printk(KERN_INFO "Hello: Device registered");
  if (alloc_chrdev_region(&first, 0, 1, "Surbhi_driver") < 0)
  {
    return -1;
  }
    if ((cl = class_create(THIS_MODULE, "accelerometer")) == NULL)
  {
    unregister_chrdev_region(first, 1);
    return -1;
  }
  for(i=0;i<3;i++){
    if (device_create(cl, NULL, MKDEV(MAJOR(first),i), NULL, "adxl_%c",ch[i]) == NULL)
  {
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    return -1;
  }
}
for(m=1;m<4;m++){
    cdev_init(&c_dev, &fops);
    if (cdev_add(&c_dev, MKDEV(MAJOR(first),(m-1)), m) == -1)
  {
    device_destroy(cl, MKDEV(MAJOR(first),(m-1)));
    class_destroy(cl);
    unregister_chrdev_region(first, m);
    return -1;
  
  }
}
  return 0;
}
 
static void __exit ofcd_exit(void) /* Destructor */
{
  cdev_del(&c_dev);
  
  class_destroy(cl);
for(p=0;p<3;p++){
  device_destroy(cl, MKDEV(MAJOR(first),MINOR(first)+p));
}
  unregister_chrdev_region(first, 1);

  printk(KERN_INFO "GoodBye: Device unregistered");
}
 
module_init(ofcd_init);
module_exit(ofcd_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Surbhi Malani");
MODULE_DESCRIPTION("My Driver");
