/*
 *    SAM-QFS_notice_begin
 *
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at pkg/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at pkg/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 *    SAM-QFS_notice_end
 */
#ifndef	_ERROR_H_
#define	_ERROR_H_

#pragma	ident	"$Revision: 1.145 $"


#include "sam/custmsg.h"	/* for GetCustMsg */

/*
 * error codes reserved for SAM/QFS management API start here.
 * see the common SAM catalog file for a list of all error messages
 */
#define	SAM_MGMT_START 30000


/*
 * maximum length of an error message
 */
#define	MAX_MSG_LEN 256

/*
 * Datastructure used both for RPC errors and for the
 * thread specific data samerrno and samerrmsg
 */
typedef struct err_struct {
	int32_t errcode;
	char errmsg[MAX_MSG_LEN];
} err_struct_t;

/*
 * error numbers specific to the SAM/QFS management API.
 */
typedef enum samapi_errno {

	SE_NODE_NOT_FOUND = SAM_MGMT_START,
	SE_FORK_EXEC_FAILED			= 30004,
	SE_MKFS_FAILED				= 30010,
	SE_MOUNT_FAILED				= 30011,
	SE_UMOUNT_FAILED			= 30012,
	SE_GROW_FAILED				= 30013,
	SE_WRITE_MODE_ERROR			= 30021,
	SE_IO_OPERATION_FAILED			= 30030,
	SE_INVALID_PROCESS_TYPE			= 30031,
	SE_POPEN_FAILED				= 30032,
	SE_PROCESS_NOT_FOUND			= 30033,
	SE_KILL_FAILED				= 30034,
	SE_CONFIG_ERROR				= 30035,
	SE_CANNOT_CREATE_PIPE			= 30036,
	SE_CREATE_FILE_FAILED			= 30037,
	SE_MCF_LINE_ERROR			= 30038,
	SE_DELETE_FILE_FAILED			= 30039,
	SE_IOCTL_FAILED				= 30040,
	SE_INVALID_SCSI_RESPONSE		= 30041,
	SE_INVALID_PARAMETER			= 30042,

	SE_AU_DISCOVERY_FAILED			= 30100,
	SE_INVALID_AU_TYPE			= 30101,
	SE_NULL_PARAMETER			= 30102,
	SE_CONFIG_MODIFIED_SINCE_INIT		= 30104,
	SE_CHECK_INIT_FAILED			= 30105,
	SE_INIT_FAILED				= 30106,
	SE_LIBRARY_NOT_INITIALIZED		= 30107,
	SE_UNABLE_TO_BACKUP_CONFIG		= 30108,
	SE_CREATE_BACKUP_DIR_FAILED		= 30109,
	SE_CONFIG_CONTAINED_ERRORS		= 30110,
	SE_CONFIG_CONTAINED_ERROR		= 30111,
	SE_INVALID_FILE_NAME			= 30113,
	SE_CFG_OPEN_FAILED			= 30114,
	SE_CFG_CLOSE_FAILED			= 30115,
	SE_FAMILY_SET_ALREADY_EXISTS		= 30116,
	SE_FAMILY_SET_DOES_NOT_EXIST		= 30117,
	SE_DEVICE_DOES_NOT_EXIST		= 30119,
	SE_INVALID_FS_TYPE			= 30120,
	SE_INVALID_DEVICE_IN_FS			= 30121,
	SE_INVALID_DEVICE_MIX_IN_FS		= 30122,
	SE_INVALID_DEVICE_STATE			= 30123,
	SE_INVALID_EQ_TYPE			= 30124,
	SE_INVALID_EQ_ORD			= 30125,
	SE_INVALID_DUMP_LOCATION		= 30126,
	SE_REQUIRED_FIELD_MISSING		= 30128,
	SE_MAX_LENGTH_EXCEEDED			= 30129,
	SE_FIELD_CONTAINED_SPACES		= 30130,
	SE_ALREADY_EXISTS			= 30131,
	SE_NOT_FOUND				= 30132,
	SE_COPY_FAILED				= 30133,
	SE_INVALID_FSCKPASS			= 30134,
	SE_UNEXPECTED_ERROR			= 30135,
	SE_VERIFY_FAILED			= 30136,
	SE_VALUE_OUT_OF_RANGE			= 30137,
	SE_INVALID_VALUE			= 30138,
	SE_INVALID_MEDIA_TYPE			= 30140,
	SE_MALFORMED_REGEXP			= 30141,
	SE_INSUFFICIENT_EQS			= 30142,
	SE_INSUFFICIENT_FREE_STRIPED_GROUP_IDS	= 30143,
	SE_NO_NO_RECYCLE_VSN_FOUND		= 30144,
	SE_NO_RECYCLE_VSN_EXIST			= 30145,
	SE_NO_ROBOT_CFG_FOUND			= 30146,
	SE_NO_RL_FS_FOUND			= 30149,
	SE_RL_FSNAME_NOT_EXIST_IN_MCF		= 30151,
	SE_NO_DRIVE_DIRECTIVE_FOUND		= 30152,
	SE_NO_BUFFER_DIRECTIVE_FOUND		= 30154,
	SE_INVALID_FSIZE			= 30157,
	SE_INVALID_INTERVAL			= 30158,
	SE_LOGFILE_CANNOT_BE_CREATED		= 30159,
	SE_SCRIPT_DOES_NOT_EXIST		= 30160,
	SE_UNABLE_TO_CHECK_ROBOT_WITH_MCF	= 30161,
	SE_UNABLE_TO_CHECK_FS_WITH_MCF		= 30162,
	SE_FSIZE_TOO_SMALL			= 30163,
	SE_FSIZE_TOO_LARGE			= 30164,
	SE_INVALID_DRIVE_COUNT			= 30165,
	SE_INVALID_AGE_PRIORITY_TYPE		= 30166,
	SE_FLOAT_OUT_OF_RANGE			= 30167,
	SE_LIST_SIZE_OUT_OF_RANGE		= 30168,
	SE_MIN_RESIDENCE_AGE_TOO_LOW		= 30169,
	SE_INVALID_DAU				= 30170,
	SE_SET_LIVE_MOUNT_OPTIONS_PARTIAL_FAILED	= 30171,
	SE_SET_LIVE_MOUNT_OPTIONS_ALL_FAILED	= 30172,
	SE_NOT_DEFINED_MNT_OPTION		= 30173,
	SE_CREATE_DIR_FAILED			= 30174,
	SE_ACTIVATE_DISKVOLS_CFG_FAILED		= 30175,
	SE_CANNOT_REMOVE_LAST_FS		= 30176,
	SE_RM_FILE_FAILED			= 30177,
	SE_PKGINFO_FAILED			= 30178,
	SE_TAIL_FAILED				= 30179,
	SE_RELEASE_FILES_FAILED			= 30180,
	SE_INVALID_LIBRARY_NAME			= 30181,
	SE_INVALID_FAMILYSET_NAME		= 30182,
	SE_INVALID_DRIVE_NAME			= 30183,
	SE_UNSUPPORTED_DRIVE			= 30184,

	SE_MMAP_FAILED				= 30200,
	SE_INVALID_REQ				= 30201,
	SE_CANT_OPEN_FLOG			= 30202,
	SE_FSTAT_FAILED				= 30203,
	SE_INVALID_SEV				= 30204,
	SE_INVALID_STATE			= 30205,
	SE_FILE_NOT_PRESENT			= 30206,
	SE_NOTF_ADDR_EXISTS			= 30207,
	SE_SYSTEM_FN_ERR			= 30208,
	SE_SINGLE_EMAIL				= 30209,
	SE_EMAIL_NOT_PRESENT			= 30210,
	SE_NO_NOTF_FILES			= 30211,
	SE_MALFORMED_NOTF_LINE			= 30212,
	SE_STAT_FAILED				= 30217,
	SE_RENAME_FAILED			= 30218,
	SE_NO_FAULT_MATCH_GIVEN_ID		= 30219,
	SE_ACK_FAULT_PARTIAL_FAIL		= 30220,
	SE_DEL_FAULT_PARTIAL_FAIL		= 30221,
	SE_ACK_MAX_FAULTS_EXCEEDED		= 30222,
	SE_DEL_MAX_FAULTS_EXCEEDED		= 30223,
	SE_ADDRESS_NOT_FOUND			= 30224,
	SE_NOTIFICATION_ALREADY_EXISTS		= 30225,
	SE_EXPLORER_FAILED			= 30226,
	SE_EXPLORER_ASYNC			= 30227,
	SE_MAIL_HEADER				= 30228,
	SE_DUMP_TITLE				= 30229,
	SE_ACSLS_TITLE				= 30230,
	SE_FS_TITLE				= 30231,
	SE_ALERT_TITLE				= 30232,

	SE_MEDIA_API_BEGIN			= 30300,
	SE_LIST_HAS_NO_MEMBER			= 30305,
	SE_FILE_READ_OPEN_FAILED		= 30309,
	SE_FILE_CLOSE_FAILED			= 30310,
	SE_FILE_CREATE_OPEN_FAILED		= 30311,
	SE_FILE_APPEND_OPEN_FAILED		= 30312,
	SE_FILE_WRITTEN_FAILED			= 30313,
	SE_SAMST_PATH_CHECK_FAILED		= 30314,
	SE_POPEN_WRITE_OPEN_FAILED		= 30315,
	SE_POPEN_READ_OPEN_FAILED		= 30316,
	SE_POPEN_WRITTEN_FAILED			= 30317,
	SE_POPEN_CLOSE_FAILED			= 30318,
	SE_DEVICE_BUSY				= 30319,
	SE_WRONG_SET				= 30322,
	SE_WRONG_FSEQ				= 30323,
	SE_NO_LIBRARY_FOUND			= 30324,
	SE_MIXED_MEDIA_LIBRARY			= 30325,
	SE_GET_EQU_ORD_FAILED			= 30326,
	SE_LIBRARY_HAS_NO_DRIVE			= 30327,
	SE_EMPTY_NAME				= 30328,
	SE_DRIVE_NOT_FOUND			= 30329,
	SE_NO_CATALOG_ENTRIES			= 30330,
	SE_NO_VSN_FOUND				= 30331,
	SE_NO_TARGET_VSN_FOUND			= 30332,
	SE_NO_TARGET_VSN_MTYPE_FOUND		= 30333,
	SE_NO_TARGET_EQ_SLOT_PART_FOUND		= 30334,
	SE_NO_TARGET_LIBEQ_FOUND		= 30335,
	SE_END_SLOT_SMALLER_THAN_START_SLOT_NO	= 30336,
	SE_NO_LIBRARY_MATCH_GIVEN_EQ		= 30338,
	SE_LIBRARY_NO_MATCH_BET_MCF_MEM		= 30339,
	SE_MCF_LIBRARY_NOT_IN_MEM		= 30340,
	SE_GET_REGEXP_FAILED			= 30341,
	SE_MASTER_SHM_NOT_FOUND			= 30343,
	SE_MASTER_SHM_ATTACH_FAILED		= 30344,
	SE_INVALID_EQ				= 30346,
	SE_NOT_A_REMOVABLE_MEDIA_DEVICE		= 30347,
	SE_UNLOAD_A_NOT_LOADED_DEVICE		= 30348,
	SE_UNABLE_TO_OPEN_COMMAND_FIFO		= 30349,
	SE_LIBRARY_ALREADY_EXIST		= 30350,
	SE_DRIVE_ALREADY_EXIST			= 30351,
	SE_NOT_TAPE_DEVICE			= 30352,
	SE_IBM3494_SUPPORT_ONLY_AUTO_DRIVE_CLEAN = 30353,
	SE_UNKNOWN_MEDIA_TYPE			= 30354,
	SE_AUDIT_AND_FOREIGN_TAPE_EXCLUSIVE	= 30355,
	SE_CATALOG_INIT_FAILED			= 30356,
	SE_VOLUME_SPECIFICATION_ERROR		= 30357,
	SE_GET_CATALOG_ENTRY_ERROR		= 30358,
	SE_DEVICE_OPEN_BY_ANOTHER_PROCESS	= 30359,
	SE_NOT_RIGHT_FLAG_FOR_CHMED		= 30360,
	SE_CATALOG_SLOT_INIT_FAILED		= 30361,
	SE_SET_CATALOG_FIELD_ERROR		= 30362,
	SE_SAM_MOVE_CARTRIDGE_FAILED		= 30363,
	SE_SAM_EXPORT_CARTRIDGE_FAILED		= 30364,
	SE_UNKNOWN_STATE			= 30365,
	SE_SET_STATE_FAILED			= 30366,
	SE_SAM_RESERVE_FAILED			= 30367,
	SE_SAM_UNRESERVE_FAILED			= 30368,
	SE_NW_ATT_LIB_TYPE_NOT_DEFINED		= 30369,
	SE_MAPPING_SYMBOL_ERROR			= 30370,
	SE_SCRATCH_POOLS_AND_SPECIFY_VSN_EXCLUSIVE = 30371,
	SE_SHARED_OBJECT_LIB_CANNOT_BE_LOADED	= 30372,
	SE_DEVICE_NOT_READY			= 30373,
	SE_NOT_A_ROBOTIC_DEVICE			= 30374,
	SE_BARCODE_MAY_ONLY_FOR_HISTORIAN	= 30375,
	SE_MEDIA_TYPE_MAY_OBLY_FOR_HISTORIAN	= 30376,
	SE_AUDIT_EOD_NOT_ALLOWED_FOR_HISTORIAN	= 30377,
	SE_IMPORT_HISTORIAN_INVALID_OPTION	= 30378,
	SE_IMPORT_STK_INVALID_OPTION		= 30379,
	SE_IMPORT_MUST_BE_VSN_OR_SCRATCH_POOL	= 30380,
	SE_SCRATCH_POOL_ONLY_SUPPORT_STK	= 30381,
	SE_ACS_QUERY_POOL_FAILED		= 30382,
	SE_ACS_RES_FAILED			= 30383,
	SE_ACS_RES_WRONG_SEQ			= 30384,
	SE_ACS_QUERY_POOL_STATUS_ERROR		= 30385,
	SE_ACS_QUERY_POOL_OPTION_INCORRECT	= 30386,
	SE_ACS_QUERY_POOL_WRONG_POOL		= 30387,
	SE_ONLY_SOME_VOLUMES_LEFT_IN_POOL	= 30388,
	SE_ACS_QUERY_SCRATCH_FAILED		= 30389,
	SE_ACS_RES_QU_SCR_FAILED		= 30390,
	SE_ACS_RES_QU_SCR_WRONG_SEQ		= 30391,
	SE_ACS_SCRATCH_NO_VOLUME		= 30392,
	SE_NOT_VOLUME_HOME			= 30393,
	SE_ACS_SET_SCRATCH_FAILED		= 30394,
	SE_ACS_RES_SET_SCR_FAILED		= 30395,
	SE_ACS_RES_SET_SCR_WRONG_SEQ		= 30396,
	SE_CANNOT_LABEL_VOLUME_IN_HISTORIAN	= 30397,
	SE_NOT_A_LEGAL_BLOCK_SIZE		= 30398,
	SE_INVALID_VSN_LENGTH			= 30399,
	SE_INVALID_CHAR_IN_VSN			= 30400,
	SE_DEVICE_CANNOT_BE_LABELED		= 30401,
	SE_OLD_VSN_DOES_NOT_MATCH_MEDIA_VSN	= 30402,
	SE_CANNOT_CREATE_RESPONSE_FIFO		= 30403,
	SE_CANNOT_RETRIEVE_CMD_RESPONSE		= 30404,
	SE_WAIT_RESPONSE_CANNOT_BE_COMPLETED	= 30405,
	SE_VSN_NOT_SPECIFIED			= 30406,
	SE_EXISTING_VSN_NOT_SPECIFIED_FOR_RELABEL = 30407,
	SE_STR_TRIM_CALL_FAILED			= 30408,
	SE_VSN_GENERATION_FAILED		= 30409,
	SE_WRONG_ROBOT_TYPE			= 30410,
	SE_WRONG_MEDIA_TYPE			= 30411,
	SE_DEVICE_NOT_AVAILABLE			= 30412,
	SE_NO_FILESYSTEM_CONFIGURED		= 30413,
	SE_UNSUPPORTED_LIBRARY			= 30414,
	SE_SAM_AUDIT_SLOT_FAILED		= 30415,
	SE_CATALOG_PATH_CHECK_FAILED		= 30416,
	SE_CATALOG_PATH_IS_DIR			= 30417,
	SE_PARAMETER_FILE_PATH_IS_DIR		= 30418,
	SE_PATH_CHECK_FAILED			= 30419,
	SE_NO_TARGET_EQ_FOUND			= 30420,
	SE_REMOVE_LIBRARY_DEPENDENCY		= 30421,
	SE_CUR_STATE_MUST_BE_OFF		= 30422,
	SE_CUR_STATE_MUST_BE_IDLE		= 30423,
	SE_CMD_FIFO_WRITE_FAILED		= 30424,
	SE_LOAD_FAILED				= 30425,
	SE_SAM_INIT_FAILED			= 30426,
	SE_CATALOG_ALREADY_EXIST		= 30427,
	SE_SAMST_CONF_NOT_EXIST			= 30428,
	SE_CUR_STATE_MUST_BE_ON			= 30429,
	SE_NO_TARGET_MEDIA_TYPE_FOUND		= 30430,
	SE_CANNOT_OPEN_MEDIA_DB			= 30431,
	SE_STK_COMMUNICATION_BROKEN		= 30432,
	SE_ACS_DISPLAY_ERROR			= 30433,
	SE_ACS_RESPONSE_ERROR			= 30434,
	SE_DLOPEN_ERROR				= 30435,
	SE_DLSYM_ERROR				= 30436,
	SE_ACSLS_CAPACITY_LIST_NULL		= 30437,
	SE_ACSLS_DEVICE_LIST_NULL		= 30438,
	SE_PID_FORK_FAILED			= 30439,
	SE_NO_STK_LIB_DRIVE_FOUND		= 30440,
	SE_EXEC_CFGADM_FAILED			= 30441,
	SE_EXEC_GREPCMD_FAILED			= 30442,
	SE_EXEC_LSSAMST_FAILED			= 30443,
	SE_EXEC_LSRMT_FAILED			= 30444,
	SE_EXEC_CP_FAILED			= 30445,
	SE_EXEC_MV_FAILED			= 30446,
	SE_EXEC_PS_FAILED			= 30447,
	SE_EXEC_KILL_FAILED			= 30448,
	SE_ACSLS_MEDIA_MAP_FAILED		= 30449,
	SE_CANNOT_GET_ACSLS_HOSTNAME		= 30450,
	SE_UNKNOWN_DEVICE			= 30451,
	SE_INVALID_VSN_RANGE			= 30452,
	SE_ACS_REQUEST_ERR			= 30453,
	SE_ACS_RESPONSE_ERR			= 30454,
	SE_ACS_START_CLIENT_FAILED		= 30455,

	SE_FILE_SYSTEM_BEGIN			= SAM_MGMT_START + 500,
	SE_FS_CONTAINS_NO_DEVICES		= 30501,
	SE_FS_CONTAINS_NO_DATA_DEVICES		= 30502,
	SE_FS_CONTAINS_NO_METADATA_DEVICES	= 30503,
	SE_FS_METADATA_DEV_REQUIRED		= 30504,
	SE_DEVICE_ALREADY_EXISTS		= 30506,
	SE_INVALID_DEVICE_PATH			= 30507,
	SE_STRIPE_GROUP_CONTAINED_NO_DISKS	= 30508,
	SE_VFSTAB_ENTRY_ALREADY_EXISTS		= 30509,
	SE_VFSTAB_TOO_MANY_FIELDS		= 30510,
	SE_VFSTAB_TOO_FEW_FIELDS		= 30511,
	SE_UNRECOGNIZED_VFSTAB_ERROR		= 30512,
	SE_GET_FS_STATUS_FAILED			= 30513,
	SE_GET_FS_INFO_FAILED			= 30514,
	SE_GET_FS_PARTS_FAILED			= 30515,
	SE_INVALID_FS_DEVICE_FOUND		= 30516,
	SE_FORK_FAILED				= 30518,
	SE_PS_FAILED				= 30519,
	SE_OPENDISK_FAILED			= 30520,
	SE_LLSEEK_FAILED			= 30521,
	SE_READ_FAILED				= 30522,
	SE_READ_INCOMPLETE			= 30523,
	SE_NOT_IMPLEMENTED			= 30524,
	SE_FS_MOUNTED				= 30525,
	SE_FS_NOT_MOUNTED			= 30526,
	SE_NO_FS_ARE_MOUNTED			= 30527,
	SE_CONN_REFUSED				= 30528,
	SE_COPIES_REQUIRED			= 30529,
	SE_VSNS_REQUIRED			= 30530,
	SE_VSNS_MUST_MATCH_COPIES		= 30531,
	SE_NOT_A_DEFAULT_SET			= 30532,
	SE_ONLINE_GROW_FAILED			= 30533,
	SE_ONLINE_GROW_FAILED_SBLK_V1  		= 30534,
	SE_SET_DISK_STATE_FAILED		= 30535,
	SE_SET_DISK_STATE_FS_NOT_MOUNTED	= 30536,
	SE_CANNOT_DISABLE_MM_ALLOCATION		= 30537,
	SE_FS_DEV_RELEASE_FAILED		= 30538,
	SE_FS_DEV_REMOVE_FAILED			= 30539,
	SE_GET_SHRINK_OPTS_FAILED		= 30540,
	SE_SHRINK_FS_NOT_MOUNTED		= 30541,
	SE_SHRINK_REPLACEMENT_GROUP_REQUIRED	= 30542,
	SE_EQ_NOT_FOUND				= 30543,
	SE_PATH_NOT_FOUND			= 30544,

	SE_ARCHIVE_BEGIN = SAM_MGMT_START + 600,
	SE_MAP_ALREADY_EXISTS			= 30601,
	SE_POOL_ALREADY_EXISTS			= 30602,
	SE_POOL_IN_USE				= 30603,
	SE_CANNOT_REMOVE_COPY_MAP_EXISTS	= 30605,
	SE_CANNOT_REMOVE_COPY_PARAMS_EXIST	= 30606,
	SE_AR_RUN_FAILED			= 30607,
	SE_AR_IDLE_FAILED			= 30608,
	SE_AR_RESTART_FAILED			= 30609,
	SE_AR_STOP_FAILED			= 30610,
	SE_GET_ARCHIVERD_STATE_FAILED		= 30611,
	SE_INVALID_RESERVE			= 30612,
	SE_GET_ARCHREQS_FAILED			= 30613,
	SE_ARCHREQ_VERSION_MISMATCH		= 30614,
	SE_CANNOT_GET_ARCHREQ			= 30615,
	SE_SAMD_CONFIG_FAILED			= 30616,
	SE_ARCHIVER_CMD_CONTAINED_ERRORS	= 30617,
	SE_ARCHIVER_CMD_CONTAINED_WARNINGS	= 30618,
	SE_ARCHIVER_FAILED			= 30619,
	SE_ACTIVATE_ARCHIVER_CFG_FAILED		= 30620,
	SE_SAMD_START_FAILED			= 30621,
	SE_SAMD_STOP_FAILED			= 30622,
	SE_CHECK_GROUP_FAILED			= 30623,
	SE_DUPLICATE_FILE_PROPS			= 30624,
	SE_CANNOT_DELETE_DEFAULT_SET		= 30625,
	SE_AR_RERUN_FAILED			= 30626,
	SE_NO_FS_NO_ARCHIVING			= 30627,
	SE_INVALID_SCANLIST_VAL			= 30628,
	SE_ARCHIVE_FILES_FAILED			= 30629,

	/* CSN Registration Errors Reserved 30700 - 30750 */
	SE_INVALID_REG_PARAMS			= 30700,
	SE_CSN_PRODUCT_REG_FAILED		= 30701,

	/* CSN errors from libcsn 30710 ... */
	SE_CANT_WRITE_TO_DATA_DIR		= 30710,
	SE_CANT_READ_DATA			= 30711,
	SE_AUTHENTICATION_FAILED		= 30712,
	SE_REG_SERVER_FAILURE			= 30713,
	SE_COULDNT_RESOLVE_PROXY		= 30714,
	SE_COULDNT_RESOLVE_HOST			= 30715,
	SE_BAD_SERVER_CERTIFICATE		= 30716,
	SE_OPERATION_TIMED_OUT			= 30717,

	SE_SAMRPC_API_BEGIN =  SAM_MGMT_START + 800,
	SE_RPC_CANNOT_CREATE_CLIENT		= 30801,
	SE_RPC_INVALID_CLIENT_HANDLE		= 30802,
	SE_RPC_FAILED				= 30803,
	SE_RPC_OUT_OF_SYNC			= 30804,
	SE_RPC_NOT_YET				= 30805,
	SE_RPC_TIMEDOUT				= 30806,
	SE_NETWORK_DOWN				= 30807,
	SE_PROC_UNAVAILABLE			= 30808,
	SE_RPC_UNKNOWN_CLIENT			= 30809,
	SE_RPC_INSECURE_CLIENT			= 30810,
	SE_RPC_PING_FAILED			= 30811,

	SE_LOAD_API_BEGIN =  SAM_MGMT_START + 900,
	SE_PREVIEW_SHM_NOT_FOUND		= 30901,
	SE_PREVIEW_SHM_ATTACH_FAILED		= 30902,
	SE_INDEX_NOT_IN_PREVIEW			= 30903,
	SE_VSN_INDEX_INCONSISTENT		= 30904,
	SE_VSN_NOT_FOUND			= 30905,
	SE_CMD_FIFO_OPEN_FAILED			= 30906,

	SE_STAGE_API_BEGIN =  SAM_MGMT_START + 920,
	SE_STAGE_OPEN_FAILED			= 30921,
	SE_STAGE_FSTAT_FAILED			= 30922,
	SE_STAGE_MMAP_FAILED			= 30923,
	SE_STAGE_INVALID_VOLUME			= 30924,
	SE_STAGE_CMD_FAILED			= 30925,
	SE_STAGE_STAT_FAILED			= 30926,
	SE_STAGE_NOT_SAM_FILE			= 30927,
	SE_STAGE_CANCEL_FAILED			= 30928,
	SE_OPENDIR_FAILED			= 30929,
	SE_CHDIR_FAILED				= 30930,
	SE_CLOSEDIR_FAILED			= 30931,
	SE_REALLOC_FAILED			= 30932,
	SE_GETCWD_FAILED			= 30933,
	SE_INVALID_STAGING_FILE_NAME		= 30934,
	SE_STAGERD_NOT_RUN			= 30935,
	SE_ACTIVATE_STAGER_CFG_FAILED		= 30936,
	SE_MUTUALLY_EXCLUSIVE_STG_OPTS		= 30937,
	SE_STAGE_FAILED				= 30938,
	SE_STAGE_PARTIAL_FAILURE		= 30939,
	SE_STAGE_DAEMON_NOT_RUNNING		= 30940,
	SE_STAGE_DAEMON_WAITING			= 30941,
	SE_STAGER_RUN_FAILED			= 30942,
	SE_STAGER_IDLE_FAILED			= 30943,
	SE_STAGER_CLEAR_FAILED			= 30944,
	SE_STAGE_FAILED_IN_RPC_CLIENT		= 30945,

	SE_LICENSE_API_BEGIN =  SAM_MGMT_START + 980,
	SE_CANT_STAT				= 30981,
	SE_MOD_TIME				= 30982,
	SE_CANT_OPEN				= 30983,
	SE_CANT_READ				= 30984,
	SE_LIC_DATA				= 30985,
	SE_UNKNOWN_ROBOT			= 30986,
	SE_UNKNOWN_MEDIA			= 30987,
	SE_NO_MEM				= 30988,
	SE_DUPLICATE_ENTRY			= 30989,
	SE_NO_MORE_ELEMENTS			= 30990,
	SE_LICENSE_NOT_ENABLED			= 30992,
	SE_QFS_LICENSE_FOR_SAM_INSTALL		= 30993,
	SE_SAM_LICENSE_FOR_QFS_INSTALL		= 30994,
	SE_CANT_GET_CLIENTS			= 30995,

	/* shared file systems errors */
	SE_SHARED_BEGIN				= 31100,
	SE_INVALID_NULL_HOST_CONFIG		= 31101,
	SE_HOST_TYPE_NOT_SET			= 31102,
	SE_SHAREFS_FAILED			= 31103,
	SE_HOST_NOT_FOUND			= 31104,
	SE_NO_ADDRESSES_SPECIFIED		= 31105,
	SE_UNABLE_TO_READ_RAW_HOSTS		= 31106,
	SE_UNABLE_TO_GET_HOSTS_FROM_CORE	= 31107,
	SE_UNABLE_TO_CONVERT_HOSTS_FILE		= 31108,
	SE_CLIENTS_HAVE_NO_HOSTS_FILE		= 31109,
	SE_ONLY_SHARED_HAVE_HOSTS		= 31110,
	SE_CANNOT_DETERMINE_RAW_SLICE		= 31111,
	SE_FS_MNTD_CANT_DEL_CLT			= 31112,
	SE_FS_HAS_NO_HOSTS_INFO			= 31113,
	SE_UPDATE_AND_WRITE_LOCAL_SET		= 31114,
	SE_DUPLICATE_HOST			= 31115,
	SE_EQU_ORD_IN_USE			= 31116,
	SE_DEV_HAS_NO_SUPERBLOCK		= 31117,
	SE_NO_DEVS				= 31118,
	SE_WRONG_FS_NAME			= 31119,
	SE_WRONG_FS_EQ				= 31120,
	SE_FS_EQ_MISMATCH			= 31121,
	SE_INIT_MISMATCH			= 31122,
	SE_MM_COUNT_MISMATCH			= 31123,
	SE_DATA_COUNT_MISMATCH			= 31124,
	SE_DEVICE_TYPE_WRONG			= 31125,
	SE_MM_COUNT_WRONG			= 31126,
	SE_DATA_COUNT_WRONG			= 31127,
	SE_DEV_COUNT_WRONG			= 31128,
	SE_DEVICE_NOT_FOUND			= 31129,
	SE_WRONG_EQ				= 31130,
	SE_UNABLE_TO_DETERMINE_HOST_STATUS	= 31131,
	SE_UNABLE_TO_GET_HOSTNAME		= 31132,
	SE_CANT_FIX_BYTE_ORDER			= 31133,
	SE_LOCAL_HOST_READ_FAILED		= 31134,
	SE_SET_ADV_CFG_BAD_INPUT		= 31135,
	SE_CANT_GET_HOST_IPS			= 31136,
	SE_CLNT_TBL_OUT_OF_SYNC			= 31137,
	SE_HOST_KV_TOO_LONG			= 31138,
	SE_INVALID_CLIENT_STATE_ARG		= 31139,
	SE_INVALID_CLIENT_STATE			= 31140,
	SE_CANNOT_DISABLE_MDS			= 31141,

	/* Sam restore errors */
	SE_NOKEYVALUE				= 31200,
	SE_NOTKEYWORD				= 31201,
	SE_BADDESTDIR				= 31202,
	SE_BADSCRIPT				= 31203,
	SE_BADCOMPRESS				= 31204,
	SE_MISSINGKEY				= 31205,
	SE_NOSUCHPATH				= 31206,
	SE_NOSUCHFS				= 31207,
	SE_NOTAFILE				= 31208,
	SE_CANT_READ_FILE			= 31209,
	SE_BAD_DUMP_FILE			= 31210,
	SE_CONFUSED				= 31211,
	SE_NOT_A_DIR				= 31212,
	SE_RESTOREBUSY				= 31213,
	SE_FILE_ALREADY_EXISTS			= 31214,
	SE_MISMATCHEDARGS			= 31215,
	SE_NOSEGMENTEDFILE			= 31216,
	SE_SAMRESTOREFAIL			= 31217,
	SE_NOTDUMPFILE				= 31218,
	SE_NOSUCHUSER				= 31219,
	SE_NOSUCHGROUP				= 31220,
	SE_CANT_TAKE_DUMP			= 31221,
	SE_DUMP_PRESCRIPT_NOTFOUND		= 31222,
	SE_DUMP_COMPRESS_FAILED			= 31223,
	SE_DUMP_SIZE_INCONSISTENT		= 31224,
	SE_IDRESTOREFAIL			= 31225,
	SE_DIRNOCOPY				= 31226,
	SE_BADSTAGE				= 31227,
	SE_DUMP_PRESCRIPT_FAILED		= 31228,
	SE_DUMP_SIZE_0				= 31229,
	SE_DUMP_INDEX_FAILED			= 31230,
	SE_DUMP_FS_NOT_MOUNTED			= 31231,
	SE_NORESULTS				= 31232,
	SE_MAIL_SUBJECT_NOTIFICATION_SETUP	= 31233,
	SE_MAIL_MSG_CONFIRM_NOTIFICATION_SETUP	= 31234,
	SE_NO_SUCH_ACTIVITY			= 31235,
	SE_RESTORE_FAILED			= 31236,
	SE_SNAPSHOT_STARTED			= 31237,
	SE_SNAPSHOT_COMPLETE			= 31238,
	SE_CORRUPT_INDEX			= 31239,
	SE_START_RESTORE			= 31240,
	SE_FINISH_RESTORE			= 31241,
	SE_DECOMP_GOING				= 31242,
	SE_RESTORE_FAILURE			= 31243,
	SE_DUMP_FAILED				= 31244,
	SE_BAD_PRESCRIPT			= 31245,
	SE_BAD_POSTSCRIPT			= 31246,
	SE_DUMP_FAILED_NODIR			= 31247,
	SE_DUMP_DUMPEXISTS			= 31248,
	SE_DUMP_INDEXEXISTS			= 31249,
	SE_DUMP_ZEXISTS				= 31250,
	SE_DUMP_GZEXISTS			= 31251,
	SE_DUMP_MOREINFO			= 31252,
	SE_DUMP_ROOTMAIL			= 31253,
	SE_DUMP_SNAPBUSY			= 31254,
	SE_DUMP_BADEXEC				= 31255,
	SE_DUMP_BADFORK				= 31256,
	SE_DUMP_POSTSCRIPT_NOTFOUND		= 31257,
	SE_DUMP_POSTSCRIPT_FAILED		= 31258,
	SE_SNAPSHOT_NOTIFICATION_SUBJECT	= 31259,
	SE_FS_OVERFLOW_NOTIFICATION_SUBJECT	= 31260,
	SE_SEE_RESTORE_LOG			= 31261,
	SE_SNAP_DIR_CREATED			= 31262,
	SE_DUMP_TIME_INCONSISTENT		= 31263,
	SE_DUMP_INTERVAL_TOO_SHORT		= 31264,
	SE_SNAP_PATTERN_BAD			= 31265,
	SE_SNAP_PURGED				= 31266,
	SE_SNAP_LOCK_FAILED			= 31267,
	SE_SNAP_UNLOCK_FAILED			= 31268,
	SE_SNAP_CANT_DELETE			= 31269,
	SE_RESTORE_NOT_SAMFS			= 31270,
	SE_CANT_DECOMPRESS			= 31271,
	SE_INDEX_NOT_DELETED			= 31273,
	SE_DUMP_FAILED_SEE_LOG			= 31274,

	/* Diskvols Errors */
	SE_DV_DICT_OPEN_FAILED			= 31300,
	SE_DV_DICT_PUT_FAILED			= 31301,
	SE_HC_NEEDS_IP				= 31302,
	SE_DV_NEEDS_NAME			= 31303,

	SE_ACTIVITY_DESCRIPTION_BEGIN		= 31400,
	SE_FSD_DAEMON_NAME			= 31400,
	SE_ACHIVER_DAEMON_NAME			= 31401,
	SE_ARCHIVER_MONITOR			= 31402,
	SE_STAGER_DAEMON_NAME			= 31403,
	SE_STAGE_ALL_DAEMON_NAME		= 31404,
	SE_AMLD_DAEMON_NAME			= 31405,
	SE_MANUALLY_MOUNTED_MONITOR		= 31406,
	SE_CATSERVER_DAEMON_NAME		= 31407,
	SE_MGMT_DAEMON_NAME			= 31408,
	SE_ROBOT_MONITOR			= 31409,
	SE_SCSI_DAEMON_NAME			= 31410,
	SE_STK_DAEMON_NAME			= 31411,
	SE_IBM_DAEMON_NAME			= 31412,
	SE_SONY_DAEMON_NAME			= 31413,
	SE_SHARED_FS_DAEMON_NAME		= 31414,
	SE_REMOTE_SVR_DAEMON_NAME		= 31415,
	SE_REMOTE_CLNT_DAEMON_NAME		= 31416,
	SE_RFT_DAEMON_NAME			= 31417,
	SE_RELEASER_NAME			= 31418,
	SE_RECYCLER_NAME			= 31419,
	SE_NRECYCLER_NAME			= 31430,
	SE_ACTIVITY_DESCRIPTION_END		= 31500,

	/* Trace and log file DESC */
	SE_DEVICE_LOG_DESC			= 31501,
	SE_HISTORIAN_DESC			= 31502,
	SE_SYSTEM_LOG_DESC			= 31503,
	SE_ARCHIVE_LOG_DESC			= 31504,
	SE_ARCHIVE_GLOBAL_LOG_DESC		= 31505,
	SE_RELEASE_LOG_DESC			= 31506,
	SE_RELEASE_GLOBAL_LOG_DESC		= 31507,
	SE_RECYCLE_LOG_DESC			= 31508,
	SE_STAGE_LOG_DESC			= 31509,
	SE_TYPE_LOG				= 31510,
	SE_TYPE_TRACE				= 31511,
	SE_STATE_ON				= 31512,
	SE_STATE_OFF				= 31513,
	SE_RESTORE_LOG_DESC			= 31514,
	SE_ARCHITECTURE_FAILED			= 31515,
	SE_INVALID_HOSTNAME			= 31516,
	SE_SOLARIS_SYSTEM_LOG_DESC		= 31517,
	SE_LOG_EMERG				= 31518,
	SE_LOG_ALERT				= 31519,
	SE_LOG_CRIT				= 31520,
	SE_LOG_ERR				= 31521,
	SE_LOG_WARNING				= 31522,
	SE_LOG_NOTICE				= 31523,
	SE_LOG_INFO				= 31524,
	SE_LOG_DEBUG				= 31525,
	/* configuration status msgs */
	SE_MCF_ERR_MSG				= 31551,
	SE_SAMFS_ERR_MSG			= 31552,
	SE_DISKVOLS_ERR_MSG			= 31553,
	SE_DEFAULTS_ERR_MSG			= 31554,
	SE_RELEASER_ERR_MSG			= 31555,
	SE_RECYCLER_ERR_MSG			= 31556,
	SE_STAGER_ERR_MSG			= 31557,
	SE_ARCHIVER_ERR_MSG			= 31558,
	SE_ARCHIVER_NO_VSNS_DEFINED		= 31559,
	SE_ARCHIVER_NO_VSNS_AVAIL		= 31560,
	SE_CONFIG_STATUS_UNKNOWN		= 31561,
	SE_CFG_STAT_STR_UNKNOWN			= 31562,
	SE_CFG_STAT_STR_OK			= 31563,
	SE_CFG_STAT_STR_ERR			= 31564,
	SE_CFG_STAT_STR_WARN			= 31565,
	SE_CFG_STAT_STR_NOFILE			= 31566,
	SE_NO_VOLS_MATCH_STR			= 31567,
	SE_NO_MCF_ERR_MSG			= 31568,
	SE_CONFIG_REQUIRED			= 31569,

	SE_EVENT_REPEAT				= 31600,
	SE_EVENT_REPEAT_MSG_FORMAT		= 31601,

	SE_FIND_NFS_FAILED			= 31700,
	SE_SET_NFS_OPTS_FAILED			= 31701,
	SE_ERROR_BAD_NFS_OPTS			= 31702,
	SE_ERROR_NFS_SHARE			= 31703,
	SE_ERROR_NFS_UNSHARE			= 31704,
	SE_ERROR_NFS_REMOVE			= 31705,
	SE_ERROR_NFS_NOPATH			= 31706,
	SE_ERROR_NFS_NOT_SUBDIR			= 31707,
	SE_ERROR_NFSD_NOT_STARTED		= 31708,
	SE_ERROR_NFS_UNKNOWN			= 31709,

	/* SAM File Operations */
	SE_VSN_STAT_FAILED			= 31800,
	SE_SEGMENT_STAT_FAILED			= 31801,

	/* SunCluster related errors */
	SE_SC_CANT_GET_VER			= 31900,
	SE_SC_CANT_GET_NAME			= 31901,
	SE_SC_CANT_GET_NODES_NAMES		= 31902,
	SE_SC_CANT_GET_NODES_STATUS		= 31903,
	SE_SC_CANT_GET_NODES_IDS		= 31904,
	/* getting webconsole and PlexMgr state */
	SE_CANT_GET_WEBCONS_STATE		= 31950,
	SE_CANT_RUN_SMREG			= 31951,

	/* monitor and report related errors */
	SE_SEND_REPORT_FAILED			= 32000,
	SE_FILE_READ_FAILED			= 32001,
	SE_MEDIA_REPORT_NAME			= 32002,
	SE_FS_REPORT_NAME			= 32003,
	SE_ACSLS_REPORT_NAME			= 32004,
	SE_ACSLS_HARDWARE_ERROR			= 32005,
	SE_ACSLS_SERV_ERROR			= 32006,
	SE_ACSLS_MAINTANCE			= 32007,
	SE_ACSLS_DEGRADED_MODE			= 32008,
	SE_ACSLS_SERV_CONFIG_MISMATCH		= 32009,
	SE_ACSLS_SERV_LOG_ERROR			= 32010,
	SE_ACSLS_RESOURCE_OFFLINE		= 32011,
	SE_ACSLS_RESOURCE_SERIAL_NUM_CHG	= 32012,
	SE_ACSLS_RESOURCE_LMU_NEW_MASTER	= 32013,
	SE_ACSLS_RESOURCE_DRIVE_CLEAN_REQUEST	= 32014,
	SE_ACSLS_RESOURCE_DRIVE_ADDED		= 32015,
	SE_THREAD_CREATION_FAILED		= 32016,
	SE_FSMDB_CONNECT_FAILED			= 32017,
	SE_FILE_METRIC_REPORT_FAILED		= 32018,
	SE_INVALID_REPORT_REQUESTED		= 32019,
	SE_NO_METRICS_AVAILABLE			= 32020,

	/* Intelistore Errors */
	SE_CANNOT_DELETE_DEFAULT_POLICY		= 32100,
	SE_INAPPROPRIATE_CLASS_DELETION_API	= 32101,
	SE_DEFAULT_PRIO_ERR			= 32102,

	/* Task Schedule Errors */
	SE_UNRECOGNIZED_TASK			= 32156,
	SE_CANT_DELETE_SCHED			= 32157,
	SE_CANT_ADD_SCHED			= 32158,
	SE_INVALID_PERIOD			= 32159,
	SE_STARTTIME_REQUIRED			= 32160,
	SE_PERIODICITY_REQUIRED			= 32161,
	SE_DURATION_REQUIRED			= 32162,
	SE_INVALID_DATESPEC			= 32163,

	SE_UNABLE_TO_GET_HWMEXCEED		= 32200,

	/*
	 * to be filled in as the API is implemented
	 * all should have the same prefix SE_ (SAM Error)
	 */

} sam_errno_t;

/*
 * these will be set by API functions before they return an error (-1)
 */
#if defined(_REENTRANT)

/* thread-specific data function */
void* fsm_err_tsd(int which);

/* thread-specific data macros */
#define	samerrno (*((int *)fsm_err_tsd(1)))
#define	samerrmsg ((char *)fsm_err_tsd(2))

#else

sam_errno_t samerrno;
char samerrmsg[MAX_MSG_LEN];

#endif	/* _REENTRANT */

#endif	/* _ERROR_H_ */
