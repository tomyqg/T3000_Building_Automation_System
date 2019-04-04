#pragma once

#include "address.h"
#include "abort.h"
#include "alarm_ack.h"
#include "apdu.h"
#include "arcnet.h"
#include "arf.h"
#include "awf.h"
#include "bacaddr.h"
#include "bacapp.h"
#include "bacdcode.h"
#include "bacdef.h"
#include "bacdevobjpropref.h"
#include "bacenum.h"
#include "bacerror.h"
#include "bacint.h"

#include "bacprop.h"
#include "bacpropstates.h"
#include "bacreal.h"
#include "bacstr.h"

#include "bactext.h"
#include "bigend.h"
//#include "bip.h"
#include "bits.h"
#include "bvlc.h"
#include "bytes.h"
#include "client.h"
#include "config.h"
#include "cov.h"
#include "crc.h"
//#include "datalink.h"
#include "datetime.h"
#include "dcc.h"
#include "debug.h"
#include "dlenv.h"
#include "dlmstp.h"
#include "ethernet.h"
#include "event.h"
#include "fifo.h"
#include "filename.h"
#include "get_alarm_sum.h"
#include "getevent.h"
#include "handlers.h"
#include "iam.h"
#include "ihave.h"
#include "indtext.h"

#include "key.h"
#include "keylist.h"
#include "lso.h"
#include "memcopy.h"
#include "mstp.h"
#include "mstpdef.h"
#include "mstptext.h"
#include "mydata.h"
#include "npdu.h"
#include "objects.h"
#include "proplist.h"
#include "ptransfer.h"
#include "rd.h"
#include "readrange.h"
#include "reject.h"
#include "ringbuf.h"
#include "rp.h"
#include "rpm.h"
#include "sbuf.h"
#include "timestamp.h"
#include "timesync.h"
#include "tsm.h"
//#include "txbuf.h"
#include "version.h"
#include "whohas.h"

#include "whois.h"
#include "wp.h"
#include "wpm.h"
#include "trendlog.h"
#include "stdbool.h"
#include "nc.h"
#include "msv.h"
#include "mso.h"
#include "ms-input.h"
#include "lsp.h"
#include "lo.h"
#include "lc.h"
#include "device.h"
#include "csv.h"
#include "bv.h"
#include "bo.h"
#include "bi.h"
#include "bacfile.h"
#include "av.h"
#include "ao.h"
#include "ai.h"
#include "h_pt_a.h"


typedef struct bacnet_rp_info  //bacnet 相关的部分必须放在 bacnet include 的头文件中;//Fan
{
    unsigned int bacnet_instance;
    BACNET_OBJECT_TYPE object_type;
    uint32_t object_item_number;
    int property_id;
    BACNET_APPLICATION_DATA_VALUE value;
    int invoke_id;
}str_bacnet_rp_info;

//#include ""
//#include ""
//#include ""
//#include ""
//#include ""
//#include ""
//#include ""
//#include ""
//#include <stdint.h>
////#include <stdbool.h>
//INPUT int abort_encode_apdu(
//	uint8_t * apdu,
//	uint8_t invoke_id,
//	uint8_t abort_reason,
//	bool server);
//
//INPUT int abort_decode_service_request(
//	uint8_t * apdu,
//	unsigned apdu_len,
//	uint8_t * invoke_id,
//	uint8_t * abort_reason);