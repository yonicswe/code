

#include <linux/syscalls.h>
		      
/*!---------------------------------------------------------------------------
 @description
	Get a value from the file, for a given key

 @returns
	NULL - failed
------------------------------------------------------------------------------*/
/*
char*
get_key_val (char *file_name,		//!< IN - name and path of the config file.
	     char *key,		//!< IN - key to search in file.
	     char *res_buf,		//!< OUT - the value
	     int   res_buf_size)	//!< IN - result buffer size.
{
	int conf_file = -1;
	char ch = 0;
	int i=0, rv;
	mm_segment_t oldfs;

	oldfs = get_fs();
	set_fs(get_ds());

	// open the file
	if ((conf_file = sys_open (file_name, O_RDONLY, 0)) < 0) {
		set_fs(oldfs);
		printk("failed to open file %s, for key=%s error=%d\n",
		       file_name, key, conf_file);
		return NULL;
	}

	printk("%s() opened file %s for key=%s\n", __func__, file_name, key);

	do {
		rv = sys_read(conf_file ,(char*)&ch, 1);

		if (rv < 0) {
			printk("failed to read from file %si error=%d\n", file_name, rv);
			break;
		}

		if ( (0 != rv) && ('\n' != ch) ) {
			if (!isspace(ch))
				if (i < res_buf_size)
					res_buf[i++] = ch;
		}
		else {
			if (i < res_buf_size)
				res_buf[i] = '\0';
			else
				res_buf[res_buf_size - 1]  = '\0';

			if ((strstr (res_buf, key) == res_buf) && (res_buf[strlen(key)] == '=')) {
				// key, found
				sys_close (conf_file);
				set_fs(oldfs);
				printk("%s() found [%s]\n", __func__, res_buf);
				return res_buf + strlen(key) + 1;
			}
			i = 0;
		}
	} while (rv == 1);

	sys_close (conf_file);
	set_fs(oldfs);

	return NULL;
}
*/
