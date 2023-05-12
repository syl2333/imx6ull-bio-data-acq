<template>
    <div>
        <v-avatar size="128px" >
            <img src="../assets/firekeeper.jpg" alt="logo" class="fill-avatar" draggable="false">
        </v-avatar>
        <div>
            <h3 class="author-text">通信1191 尚以龙 毕业设计作品</h3>
            <p class="author-github">Github项目链接
                <a href="https://github.com/syl2333/imx6ull-bio-data-acq">
                    imx6ull-bio-data-acq
                </a>
            </p>
            <p class="author-email">本人邮箱 yilongshang233@gmail.com</p>
            <vue-qrcode :value="url" :options="{ width: 200, margin: 1 }"></vue-qrcode>
        </div>
    </div>
    
</template>

<script>
import VueQrcode from 'vue-qrcode';   
export default ({
    name: 'FeedBack',
    components: {
        VueQrcode
    },
    data() {
        return {
            url: "https://github.com/syl2333/imx6ull-bio-data-acq"
        }
    }
})
</script>

<style>
.fill-avatar {
    object-fit: cover; /* 图片会被剪裁以填充容器，但保持其比例 */
    width: 100%; /* 图片宽度为容器的宽度 */
    height: 100%; /* 图片高度为容器的高度 */
}
.author-text {
    margin-top: 45px;
    color: black;
}
.author-github {
    margin-top: 15px;
}
.author-email, .author-github {
    margin-top: 15px;
    font-size: 16px;
    color: black;
}
</style>