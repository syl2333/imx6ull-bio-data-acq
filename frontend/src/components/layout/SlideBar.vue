<template>
    <v-card>
        <v-layout>
            <v-navigation-drawer expand-on-hover rail>
                <v-list>
                    <v-list-item prepend-avatar="https://randomuser.me/api/portraits/women/85.jpg" title="Sandra Adams"
                        subtitle="sandra_a88@gmailcom"></v-list-item>
                </v-list>

                <v-divider></v-divider>

                <v-list density="compact" nav>
                    <v-list-item prepend-icon="fas fa-home" title="My Files" value="myfiles">
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