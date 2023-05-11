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
                    <v-list-item prepend-icon="fas fa-home" title="首页" value="myfiles" to="/Home/dashboard">
                    </v-list-item>
                    <v-list-item prepend-icon="fas fa-plus" title="Shared with me" value="shared"></v-list-item>
                    <v-list-item prepend-icon="fas fa-minus" title="Starred" value="starred"></v-list-item>
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