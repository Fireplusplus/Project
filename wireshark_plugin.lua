local my_proto = Proto("my_proto", "My Protocol")

local p_type = ProtoField.uint8("my_proto.p_type", "Type", base.DEC);
local p_val = ProtoField.uint16("my_proto.p_val", "Val", base.HEX);
local p_byte = ProtoField.new("Bytes", "my_proto.bytes", ftypes.BYTES)
local p_str = ProtoField.new("Str", "my_proto.str", ftypes.STRING)

my_proto.fields = {
	p_type,
	p_flag,
	p_val,
	p_byte,
	p_str
}

--[[
	tvb: 待解析数据
	pinfo: 协议解析树信息，包括UI上的显示
	treeitem: 上一级解析树
--]]
function process(tvb, length, tree)
	local offset = 0
	
	tree:add(p_type, tvb:range(offset, 1))
	offset = offset + 1
	tree:add(p_val, tvb:range(offset, 2))
	offset = offset + 2
	tree:add(p_byte, tvb:range(offset, 10))
	offset = offset + 10
	tree:add(p_str, tvb:range(offset, 13))
	offset = offset + 13
	
	local left = length - offset
	tree:add(p_byte, tvb:range(offset, left))
end

function my_proto.dissector(tvb, pinfo, treeitem)
	pinfo.cols.protocol:set("MY_PROTO")
	pinfo.cols.info:set("MY_PROTO info")
	
	local tree = treeitem:add(my_proto, tvb:range(0))
	process(tvb, tvb:len(), tree)
end

-- 绑定UDP端口号57754, 凡是匹配的报文都会调用my_proto.dissector解析
local udp_table = DissectorTable.get("udp.port")
udp_table:add(57754, my_proto)
