#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/random.h>


unsigned char get_random_byte(int max) {
    unsigned char c;
    get_random_bytes(&c, 1);
	return (c%max+1);
}

int get_dice_roll(void){

	return roll;
}

static ssize_t dice_read(struct file * file, char * buf, size_t count, loff_t *ppos)
{
	int i = get_dice_roll();
	
    if (i < 0)
		-EINVAL;
    /*
	 * We only support reading the whole string at once.
	 */
	if (count < sizeof(int))
		return -EINVAL;
	/*
	 * If file position is non-zero, then assume the string has
	 * been read and indicate there is no more data to be read.
	 */
	if (*ppos != 0)
		return 0;
	/*
	 * Besides copying the string to the user provided buffer,
	 * this function also checks that the user has permission to
	 * write to the buffer, that it is mapped, etc.
	 */
	if (copy_to_user(buf, &i, sizeof(int)))
		return -EINVAL;
	/*
	 * Tell the user how much data we wrote.
	 */
	*ppos = sizeof(int);

	return sizeof(int);
}

static const struct file_operations dice_fops = {
	.owner	= THIS_MODULE,
	.read 	= dice_read,
};

static struct miscdevice dice_dev = {
	MISC_DYNAMIC_MINOR,
	
	"dice",
	
	&dice_fops
};

static int __init dice_init(void){
	int ret;
	
	ret = misc_register(&dice_dev);
	if(ret)
		printk(KERN_ERR "Unable to register 'dice' misc device\n");
	
	return ret;
}

static void __exit dice_exit(void){
	misc_deregister(&dice_dev);
}

module_init(dice_init);
module_exit(dice_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Valerie Henson <val@nmt.edu>");
MODULE_DESCRIPTION("\"Hello, world!\" minimal module");
MODULE_VERSION("dev");
