/****************************************
 *  VFS interface
 *
 *  A filesystem should register a struct VFS with the VFS system
 *  in a driver init function. (See driver.h, macro REGISTER_INIT)
 *
 * Required functions:
 * 	s32_t vfs_fopen (struct VFS_mount * THIS, struct file * file, const char* path, mode_t mode, u32_t flags);
 *	
 *
 *
 ****************************************/
#ifndef XE_VFS_H
#define XE_VFS_H
#include <ctools.h>
#include <types.h>

/**
 * Mount a filesystem
 *
 * Try to mount \a device using the option string \a opts
 *
 * \param[in,out] THIS	The VFS interface that was used to find this function
 * \param[out] mount	Information on the freshly-mounted filesystem. Undefined if failure is returned.
 * \param[in] device	The block device to find the filesystem on
 * \param[in] opts	The option string passed when mounting the filesystem
 * \return		A value indicating success or failure
 * \retval 0		Success
 * \retval -EINVALID	Wrong FS type
 * \retval -EIO		IO error
 */
typedef s32_t (*vfs_mount)(struct VFS *THIS, struct VFS_mount *mount, struct blk_dev * device, const char* opts);
