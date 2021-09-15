function normal(shader,t_base,t_second,t_detail)
shader:begin("wmark","simple")
:sorting(2,false)
:blend(true,blend.zero,blend.srccolor)
:aref(true,0)
:zb(true,false)
:fog(true)
shader:sampler("s_base"):texture(t_base)
end