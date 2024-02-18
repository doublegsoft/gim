-- 会话信息
create table tn_gim_convo (
  convoid                  text                     not null,
  convonm                  text,
  convotyp                 text,
  opt                      text,
  sts                      text,
  primary key (convoid)
);
-- 会话成员信息
create table tv_gim_convombr (
  convoid                  text                     not null,
  mbrid                    text                     not null,
  mbrtyp                   text                     not null,
  als                      text,
  unrdcnt                  text,
  lct                      text,
  jdtm                     text,
  lvtm                     text,
  sts                      text,
  primary key (convoid,mbrid,mbrtyp)
);
-- 会话消息信息
create table tn_gim_convomsg (
  convomsgid               text                     not null,
  convoid                  text,
  sndrid                   text,
  sndrtyp                  text,
  rcvrid                   text,
  rcvrtyp                  text,
  msgtm                    text,
  msgtyp                   text,
  msgcont                  text,
  crttm                    text,
  sts                      text,
  primary key (convomsgid)
);
