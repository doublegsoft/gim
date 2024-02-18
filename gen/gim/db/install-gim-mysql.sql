-- 会话信息
drop table if exists tn_gim_convo;
create table tn_gim_convo (
  convoid                  varchar(64)              not null,
  convonm                  varchar(200),
  convotyp                 varchar(48),
  opt                      longtext,
  sts                      char(2)
);

alter table `tn_gim_convo` change `convoid` `convoid` varchar(64)
comment '会话';
alter table `tn_gim_convo` change `convonm` `convonm` varchar(200)
comment '会话名称';
alter table `tn_gim_convo` change `convotyp` `convotyp` varchar(48)
comment '会话类型';
alter table `tn_gim_convo` change `opt` `opt` longtext
comment '附加信息';
alter table `tn_gim_convo` change `sts` `sts` char(2)
comment '业务状态';

alter table tn_gim_convo add constraint pk_tn_gim_convo primary key (convoid);

-- 会话成员信息
drop table if exists tv_gim_convombr;
create table tv_gim_convombr (
  convoid                  varchar(128)             not null,
  mbrid                    varchar(64)              not null,
  mbrtyp                   varchar(64)              not null,
  als                      varchar(200),
  unrdcnt                  int,
  lct                      datetime(3),
  jdtm                     datetime(3),
  lvtm                     datetime(3),
  sts                      varchar(16)
);

alter table `tv_gim_convombr` change `convoid` `convoid` varchar(128)
comment '会话';
alter table `tv_gim_convombr` change `mbrid` `mbrid` varchar(64)
comment '成员';
alter table `tv_gim_convombr` change `mbrtyp` `mbrtyp` varchar(64)
comment '成员类型';
alter table `tv_gim_convombr` change `als` `als` varchar(200)
comment '会话别名';
alter table `tv_gim_convombr` change `unrdcnt` `unrdcnt` int
comment '未读消息数量';
alter table `tv_gim_convombr` change `lct` `lct` datetime(3)
comment '最近会话时间';
alter table `tv_gim_convombr` change `jdtm` `jdtm` datetime(3)
comment '加入时间';
alter table `tv_gim_convombr` change `lvtm` `lvtm` datetime(3)
comment '离开时间';
alter table `tv_gim_convombr` change `sts` `sts` varchar(16)
comment '业务状态';

alter table tv_gim_convombr add constraint pk_tv_gim_convombr primary key (convoid,mbrid,mbrtyp);

-- 会话消息信息
drop table if exists tn_gim_convomsg;
create table tn_gim_convomsg (
  convomsgid               varchar(64)              not null,
  convoid                  varchar(128),
  sndrid                   varchar(64),
  sndrtyp                  varchar(64),
  rcvrid                   varchar(64),
  rcvrtyp                  varchar(64),
  msgtm                    datetime(3),
  msgtyp                   varchar(64),
  msgcont                  longtext,
  crttm                    datetime(3),
  sts                      char(2)
);

alter table `tn_gim_convomsg` change `convomsgid` `convomsgid` varchar(64)
comment '会话';
alter table `tn_gim_convomsg` change `convoid` `convoid` varchar(128)
comment '会话';
alter table `tn_gim_convomsg` change `sndrid` `sndrid` varchar(64)
comment '发送者';
alter table `tn_gim_convomsg` change `sndrtyp` `sndrtyp` varchar(64)
comment '发送者类型';
alter table `tn_gim_convomsg` change `rcvrid` `rcvrid` varchar(64)
comment '接收者';
alter table `tn_gim_convomsg` change `rcvrtyp` `rcvrtyp` varchar(64)
comment '接收者类型';
alter table `tn_gim_convomsg` change `msgtm` `msgtm` datetime(3)
comment '消息时间';
alter table `tn_gim_convomsg` change `msgtyp` `msgtyp` varchar(64)
comment '消息内容';
alter table `tn_gim_convomsg` change `msgcont` `msgcont` longtext
comment '消息内容';
alter table `tn_gim_convomsg` change `crttm` `crttm` datetime(3)
comment '创建时间';
alter table `tn_gim_convomsg` change `sts` `sts` char(2)
comment '附加选项';

alter table tn_gim_convomsg add constraint pk_tn_gim_convomsg primary key (convomsgid);
