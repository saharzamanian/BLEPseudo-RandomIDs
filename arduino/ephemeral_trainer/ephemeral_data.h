#ifndef DATA_H
#define DATA_H


const size_t NUM_TRAINING_DATA = 91;
const size_t NUM_VALIDATION_DATA = 27;
const size_t NUM_TEST_DATA = 12;

const size_t NUM_INPUT_DATA_ELEMENTS = 64;


const int train_labels[NUM_TRAINING_DATA] = {
  1, 3, 2, 1, 0, 0, 0, 0, 0, 3, 3, 3, 3, 1, 0, 1, 2, 2, 1, 0, 1, 3, 0, 0, 0, 3, 1, 0, 0, 1, 3, 3, 2, 0, 3, 0, 0, 2, 2, 0, 3, 1, 2, 0, 0, 3, 1, 1, 3, 3, 2, 0, 2, 1, 1, 2, 3, 2, 3, 2, 0, 0, 1, 0, 0, 0, 0, 1, 2, 1, 3, 1, 3, 1, 3, 3, 1, 0, 0, 1, 0, 0, 1, 1, 3, 2, 1, 2, 0, 1, 3
};

const int validation_labels[NUM_VALIDATION_DATA] = {
  2, 1, 1, 1, 2, 0, 1, 3, 1, 1, 3, 3, 3, 2, 0, 1, 3, 2, 3, 3, 3, 0, 1, 0, 0, 1, 0
};

const int test_labels[NUM_TEST_DATA] = {
  3, 0, 3, 2, 0, 3, 1, 0, 1, 0, 3, 0
};

const String train_data[NUM_TRAINING_DATA] = {
  "fad286c3ee80b5b63d1e0eb5776c2aece8e9ae725813b95720c41a707c2a81",
  "d23d45e122155e8d73464efa23790bcb896e591c4a647c2844e58d9362db4",
  "e074f3aa5f2629567eae85a10d5e7e734fafd32e0846a8578382226cfc32dd",
  "3510ccead2e4b9af662015c4739546afe361531664d34bb09518568fe325a2",
  "c19243ea883cde121df747a9d5c182b3f12cf555ee87410188e87f6f6cb12da",
  "67923489c2665492827f7087a4de9fada83b4319579563d77f33fb88cb7122e9",
  "b8c2df4993e1c7f96967ccce334e11c27b7468c60766757bc75f55b1cd4a87",
  "edfa81c735520ddba7bd7b5dcdcb7edee3c34fccd95ad23effeb12e577e5f8d",
  "77f63a61a5aaa8c5c917028a1caa9e2b9424dd129e514ea1e56cd8ede61040",
  "26f6a63e687c48f7ebb14d6f486f9deb850fb342b38d6cbe21b4efc7d25",
  "911e9730d94a6b72cf1b24c97958132deacfd1a52ae4859af11a30f340321d8e",
  "825f365c7a1894b649a45d02ebfdebbc43dbb15796fd64ca7b3d2c0aaf5",
  "b8184abe5ac8b5c9b8ea5b15322716c5ce76bbe24aa9b8948f312cf4e7fb37",
  "d2375749d2c53c605f624d1fedd6a4253434b7d44061933d83ab872f9478f391",
  "9b9cf24870d9af9eeec9bacffbc68ac3aac5b2128e7baf3a35f31f9cc537",
  "f443d5528537386832310c3383083048399ebf554ff8e648b9f9947cc4514",
  "9082d15ba81523533798744fa163cac4493d668effc4042a8e35ccb149adfe",
  "cf491ec65297ea6c4199e0aea2fa2f18c332d6295a49dd455fd5a5efdcb0d5",
  "f02acbe55ab3a30ca46481eb9a9d08293234c2df0a04913412e992f1ce1470",
  "879e15187737169ab3414a538573c47f96a534c7609d26f96f9e5a5154e4f55",
  "e454d85cbbab3a99e1803dc331d9d1ad965945ff72fa285a0fa9da0f78f",
  "fd2115f171c821de58a0e4ae3df2bee14e56c02189df1cebaae3f6235b8a4d45",
  "c8d329e0c8fb30b3995fdebeb193ee7d8ab78515f1a9625119f9f30a01fb62c",
  "30b0b5ad9da79c3552aceb63f3564d5277666f94d91d9d40aa78c71f702f338e",
  "1f1940272aa2eced91ac5ac7d216f88c94ea9cf45c9ac334235d1db19fe964",
  "c8c34685e23e4c82cc8c3cb9ea4ef7da82132dff030d24dc38d5b3b789d1",
  "84bb9b2b8b927ea71b565167f4e37398b2c12fb81e3232c955799c92997029",
  "242bff63417b17dfe25b815ea125c84218c11da44d71660b2e516424dc1c",
  "d62c6fc316aec7d7c80f8f02d3126e2e81df3f13ac3b137312cb287167e5f1",
  "3bb1b1685a8d6e8f854a9b321246294817038d41770c9e539baa5327f63ea5",
  "f557b91e24c42db26b9bacee42905de2901569e50b6371eaf9c12efeb28916",
  "bd1d614cb479caf193caab4183f6843521c31e3f219f25337b257e16fe849be",
  "314a36cfa45e24a8c5f34343909ca7347c12243684e4e2a44d53edbc4a5e20",
  "f0f388cf826fb19df3d1ebe587d787f22dc515b1b45182f2c949cfb16834",
  "ee1c590a0fd93365aa357a6f486a0269935a95396d0e54d3d6a45dfbd3f6c",
  "e86f68ad57d51a84785fa3eceffcd0b7136622145fb702d4aef567dfc5114c",
  "8386886cf369d5a8eaec9ce8e22959e6231452f78783f906f168d7f633f752",
  "527dc7349ab37e9b3b1f4b8495014423d272c32fde77363538632f7443b",
  "98f5b1c76fe8f93566257a88916880bc631c7037b3d0cf6c0d7cafc62d271",
  "f1f2362f1e81e28e01ef54843425ea74397f6caddc3dcbee4d5f2c66b18989",
  "39b8e4e45b2ffbb1c7efafe5a8387050e825afc92c9ba2fde6ab443c54b81d",
  "cbe0514c664ecfff6034ff653cc2419a88859634cdc482a43fca7fdfe63",
  "ff609b5dc9aabdfc32e7a7731991d657080cde2c8d5e5992890211db85842f3",
  "657cb21828b05471cde935694721dfa15dc9752b7776a7b94ca6a6831171ecd",
  "2303cdc4355a095d812e1a2afbefe3bcc662d44ffc5251faf4d8656146ece",
  "1b26542cde8915a4ed72a0c3c75078cab25ec1ac217b208cdef95fc6908ed67",
  "4abf5fd7af487257ada64c147d10a15dabd579b5bd495e4d47c61ca5a8e4eb84",
  "e0fbc16db65baac48e4232ba87a4a8732e90369c7441d6f771a22dcf24099ce",
  "7418667ff2df6aa6ce28e69cadfbfe2aebb0ffdae4d3fe5e30e1d06bff15",
  "a4a7dafd19e2aed7227316c5a228acaf24dd94a33abcea4a3808d6c16c71a2b",
  "8038a7f4a7446e94e29a3f4149c8a33ed4fefa6f7d643283b38fbfeb2675f70",
  "32199a62f81a7d8cd229fe3d24d82645db8bd555679edf08a6f2f338847d7e3",
  "686b682a32e7411935376edb502debadfe7382766ebcd8c895385c133996e727",
  "6b503e7428221ec9a7e0ef80a68ef62f77c3b7e0ddf7e755385c38f2d74b7e5e",
  "3e2390b02cb7eb4d858dfd241d7d764adf79af18a045f5a7172f82f5d0d3d9",
  "bfe24ef51ed3c181ab1fb58a23cd94e487d84443656651e86f166eedc2ff91",
  "f0e6dec4af1238ca8edd408d1d5cb796694f9d468f9858ee8b55fb36cf87d",
  "256b882ac548bd3962c7d5a7eef81ef5022f3cff7a29d6afe88e98dd6c72553",
  "9bf982dace159326f3d29bcf60712bbf7a705c509bce17beb637e4235182ae8",
  "8edfe337fbad6ae0f25b691e1b2d6452783861c146756eabfbfe9a37b9a34",
  "4692baf3d26bef97407962062e4106eeedb9632a9d5fca375b86cc8871a26",
  "ce742982c0fc64156a93188d1686e6eaaacc9483f7d78328f33cc735830b3ab",
  "dcb32ee0825d5a9cc944c25f955f6237b35e56430ef8e743fe13ff770c7af",
  "bf60c29f487be9f2b5126b43e8e0a7a51d927165d6a94e48b84df0cbb1170b1",
  "7afed85fdb3e801e39cdc9a02f817d95a816a0d5cc9591d99a1f5bf81a7d3621",
  "b82595b91a8c51b89cf1e8dcd575ede0d46752f88b473d71715769d4b6ceb034",
  "9ac18b7634663c1f3d2f49b5bcd3805f3bcd8f7a1b666199758c2a9498263b8f",
  "df5521b8a0effe9be85ff7e0ffceec2d885a441a7cdd57e28d5e1accfe99059",
  "2ecba2b09aa1fd49775d5a6152e0f929ec1fa13d6bbc5bb14b89109f1ba5693",
  "b6d829d71779acdbc593ca7a15bf34dfb34ce7094baa2ac480706332a79",
  "8142176fd1a5896358b1a065fc30b3212637148bbc189aee92bce9ee5cc4",
  "6ba66393dc4554b713b1c61dbc010e011fe95a42fe34d051619fdeefc2d70",
  "6c96d39054f882a31464abdc45d7828c35c62e92034879860d633514ae42adb",
  "67e7ff7b63e5dbb4171f3fa813eac0a96152f4e16ea44f0b33ec2a6e5a5199",
  "d874dd9da6472313f97f4973bbde1b666c29b7f2dfd9a5f64e4162b8b2c128",
  "647786dbe2ecce2b2db36e674e779f32229df90c3c62ca8ad18f818e115730",
  "46502dc64a54b4e5d7a21d82ef37c1d157adc082ae986b874b7ce9d3464575b",
  "d85271d28239d7ca57a4b8477706cca85d2bd4e216883b83f79577c9d1e332",
  "17d847fb457276b2d1f1b34a0d3efed1bbb52b85a2c4a0de6c90c524cfefc9",
  "7c2a53bec8e1324dab68f4912dfe1c2d7195a22f32087ef1783328895e2",
  "98329ec649130469a8f9a6e2a8bb79a653138f0ba6c8a7b46fde29aaac152f",
  "dc13a0a57ff678ed584384c02f559caaad40f480891ac47d74bd4158ae15953",
  "f411b29b841b09660c559a7541ae511c1799c4fd6b83ebf49bbaa449a9141",
  "d5f9e7c2dc0c42469e726969d181a8e4dbfc3693cc2abd1967e3f7725a19a0",
  "df1980e68bfd75d0d3df836349cc2c6cfd485a8c88c0888f3fa2f9418789a",
  "5caf620aed7c53c6b6c921774ae1c0edc623fed498c060e75839a171fd664b",
  "b115f07557754c50afdd56a5e3e37abcd6d26a9ca67c4cd77c43d01d16c51",
  "f9ee1578c2fe95179feabf675d3dc66b66db9849c610493571dde7af27aeb",
  "f527928972caba029a1c607166afdaacbc60b85da59a8525e8c266925576d8",
  "e9cec65fa2933f05826fd6917a48f8251d3c4cc3fb7c9799bca6e49632117",
  "39559f9da1165339b447cf0156d9f1da8f85179a572bca84d65dbd0a8fc94c"
};

const String validation_data[NUM_VALIDATION_DATA] = {
  "35f2047ba1be3d380bf74d47ae736a64564da689d85cb76c2b6a6c6405875",
  "a66a32ea696ac3486f274e9e3890d94f66380459d5a5cb570c329696550a93",
  "208575cd63db4f98acad08dfa8b33258b17b1bf5204afb9b6be79eaec3a6",
  "12c7ffe0e1907821c62b1f92051fac342469d409311152c71988119c554ae6b",
  "b9875ab1bb7febe385c63b35505b1e88215e75ee03ca4858dcc771313dbb46b",
  "8dc0d743614d89362a2ab421814a661e7a7e183454e1ffdfae89d7070de5b70",
  "2cb5277b396df35a10eda4881aea1ee4e7c4e96be65235af889681d41b82e531",
  "2f30a45cdb88517e549fecac56cf84772996df14e6e065c9521c2efe438f99f9",
  "cdfbf4fb6bf27f8f185fd44fc774f764459aa2d5ec84d1d7a284610102b6e",
  "b2db4848b8ddcaaf1a5c58977857132de669a8615516b7df7d78f7ad618723",
  "b4349e115ac532bebcc4558bbadd348e452cc3afe49ee246ca18f6f7b8eb19",
  "7c97d1479585273d87bf549e96b9b49ec9136c405b095ac81893ceacd9c69d",
  "d5e49329952d1050c0f269a571299cc216862908ba97cbac16416d5dafe048",
  "abebe8dafca96ff1c18e374418ae56e5eab97dd97980c0205eedadde4a3b0",
  "fc2ad696e0f114adf5479b47be27e5b7e49fd99c4c13ea481586efe738903010",
  "65dbbe53659aefc4577a47b9c4b1953f863a4513f432869f53119822996feb",
  "8c1a204aec8afa35b332e8c14829cd63917333ff8e9eee2df2cefdbac31a1",
  "7c931c47959d6e99b7680f6c6c15dc2e371a3dc97e3272bda439647ae8de3c",
  "73273740fb5c42c81e7be43cc2db39bd38f8eb18df586ecd2b975dd331456ae",
  "8141ef2473262bdc6f0acdb9062c3477dbcc07744b8f56fb94481e125e0",
  "50281d166856d5d1332a4f93de9aaaf08e757a94bba3c2277c2a0a3c4c49857",
  "4ccee4ec064c786ac20489fb81e8f74d9b6b6f1235d538e1ed9b7cbd845a269",
  "c0108bde49df1acfd337ef670fb44209e5b6c21e368e96792127a88b987f9",
  "933262123124b58ceb6b6c84c3e289655b7ae5c3da2bf0d592db3d53567549",
  "107fa97b3293957794df087148a432f6149239989ee891b16a0e829bd377a",
  "3c634e5b96b14cd62d89af543184a7428f5c5963d6f44e78a778bce685379b5",
  "d0f2d73a755283869dc46dc8dbf8eb7da5acbcde105bbfa67c6e51736603dc1"
};

const String test_data[NUM_TEST_DATA] = {
  "aefad785cde4111f1d20199dbdbcb74b54cef74ee23e2625c2a651dbb82c28",
  "61403417533afd70d186a8d2b978a05286e2a1d962c6b85f3314de1b690fcc1",
  "d042a84b80df8697fae0515b15c1ca493f81f75d2416b34a1ad1d671a1a7e5",
  "3758d9e4307ecdffdaffa6ca1278a055e99a69826664861a85a1cd5c3cfb7d",
  "9d534014f9ed71ea9f5518d5c2408fa2941078a0d9aaeb216c110b6d9bb53",
  "eba4ab913047c4a747fc5790f9e145eea25b5f732331d63451abcadb1f42ef2",
  "8af6ebf22b1b9736fdccaf9e5cb8316c5f11f3cc9054c9d9bb4d2b7f2735b1e",
  "6c562b1ec27c77ac4861f18e9b8c202e281e9ddd525513168b1cb31fc6c0a5e1",
  "1964ceae461a3e6dff88758ce24d13fce251caf5196f983940dddb69b2123b",
  "6d7b375c916592656775952d8c394a3ea12121ae1fc7cb183435cab57abca",
  "d0e3180e7acdf5a9cbec6c4b392d5a09758116ab3b629d0b41c9c047f5fd76",
  "9b9f3ee56a7a7fa77277459eb34dded4332830a4d5973b8bcac1199f1121db5"
};


#endif
