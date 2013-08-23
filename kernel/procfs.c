#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <asm/io.h>

static u32 addr = 0;
static u32 data = 0;

struct proc_dir_entry *memhack_dir;
struct proc_dir_entry *memhack_addr;
struct proc_dir_entry *memhack_data;

static int
addr_read(char *page, char **start, off_t offset,
	  int count, int *eof, void *data)
{
    int len;

    len = sprintf(page, "0x%08x\n", addr);

    *eof = 1;

    return len;
}

static int
addr_write(struct file *file, const char *buf, unsigned long count, void *d)
{
    if(kstrtou32_from_user(buf, count, 16, &addr) != 0) {
	printk(KERN_ERR "kstrtou32_from_user: failed\n");
	return -EFAULT;
    }

    return count;
}

static int
data_read(char *page, char **start, off_t offset,
	  int count, int *eof, void *d)
{
    int len;

    void __iomem *p = (void*)addr;

    data = readl(p);

    len = sprintf(page, "0x%08x\n", data);

    *eof = 1;

    return len;
}

static int
data_write(struct file *file, const char *buf, unsigned long count, void *d)
{
    void __iomem *p = (void*)addr;

    if(kstrtou32_from_user(buf, count, 16, &data) != 0) {
	printk(KERN_ERR "kstrtou32_from_user: failed\n");
	return -EFAULT;
    }

    writel(data, p);

    return count;
}

int
proc_init(void)
{
    memhack_dir = proc_mkdir("memhack", NULL);
    if (memhack_dir == NULL) {
	goto err_quit;
    }

    memhack_addr = create_proc_entry("addr", 0600, memhack_dir);
    if (memhack_addr == NULL) {
	goto err_quit;
    }

    memhack_data = create_proc_entry("data", 0600, memhack_dir);
    if (memhack_data == NULL) {
	goto err_quit;
    }

    memhack_addr->read_proc  = addr_read;
    memhack_addr->write_proc = addr_write;
    memhack_data->read_proc  = data_read;
    memhack_data->write_proc = data_write;

    return 0;

err_quit:
    printk(KERN_ERR "memhack: failed to create /proc entry. Abort.\n");
    return -1;
}

void
proc_fini(void)
{
//    remove_proc_entry("data", memhack_dir);
    remove_proc_entry("addr", memhack_dir);
    remove_proc_entry("memhack", NULL);
}
