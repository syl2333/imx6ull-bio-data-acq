<template>
    <v-card>
        <v-layout>
            <v-navigation-drawer expand-on-hover rail>
                <v-list>
                    <v-list-item prepend-icon="fas fa-user" title="管理员"
                        subtitle="系统默认创建"></v-list-item>
                </v-list>

                <v-divider></v-divider>

                <v-list density="compact" nav>
                    <v-list-item prepend-icon="fas fa-home" title="首页" value="myfiles" to="/Home/DashBoard">
                    </v-list-item>
                    <v-list-item prepend-icon="fas fa-table" title="历史数据" value="shared" to="/Home/HistoryData"></v-list-item>
                    <v-list-item prepend-icon="fas fa-paper-plane" title="联系作者" value="starred" to="/Home/FeedBack"></v-list-item>
                </v-list>
            </v-navigation-drawer>
        </v-layout>
    </v-card>
</template>

<script>
export default {
    name: 'SlideBar',
};
</script>